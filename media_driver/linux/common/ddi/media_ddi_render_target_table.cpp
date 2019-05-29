/*
* Copyright (c) 2019, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
//!
//! \file     media_ddi_render_target_table.cpp
//! \brief    Defines the class for render target management.
//!

#include "media_ddi_render_target_table.h"
#include "media_libva.h"
#include "media_libva_util.h"

#include <algorithm>
#include <set>

//!
//! \brief    Init
//! \details  Initialize the render target table. Should be called prior to other interactions
//!           with the render target table. Since the input parameter is codec-specific,
//!           Init should most likely be called in the codec-specific media context initialization
//!           stage.
//!
//! \param    [in] max_num_entries
//!           Maximum number of render targets to track in the render target table. Should realistically
//!           not exceed the maximum number of the uncompressed surface buffer of the driver.
//!

void DDI_CODEC_RENDER_TARGET_TABLE::Init(size_t max_num_entries)
{
    m_current_rt_surface = VA_INVALID_ID;
    m_current_recon_target = VA_INVALID_ID;
    m_free_index_pool.clear();
    m_va_to_rt_map.clear();
    m_usedSurfaces.clear();
    m_usedSurfaces.push_back(std::vector<VASurfaceID>());

    for (RTTableIdx i = 0; i < max_num_entries; i++)
    {
        m_free_index_pool.push_back(i);
    }
}

//!
//! \brief    Register Render Target Surface
//! \details  Register surface in render target table
//!
//! \param    [in] id
//!           VASurfaceID for the render target to be registered. If there is no more place
//!           inside the render target table, one inactive render target will be evicted in order
//!           to put the new render target in its place, and an error status returned.
//!
//! \return   VAStatus
//!           VA_STATUS_SUCCESS if successful (either id has been registered, or had
//!           already been registered, or a surface eviction was
//!           required to register the new render target), VA_STATUS_ERROR_NOT_ENOUGH_BUFFER if it is
//!           impossible to register the new render target because none are marked as inactive.
//!
//!

VAStatus DDI_CODEC_RENDER_TARGET_TABLE::RegisterRTSurface(VASurfaceID id)
{
    if (id == VA_INVALID_ID)
    {
        DDI_ASSERTMESSAGE("Invalid VASurfaceID in RegisterRTSurfaces");
        return VA_STATUS_ERROR_INVALID_PARAMETER;
    }

    // the surface id participates in the latest Begin/End picture processing
    // like target, recon, reference frame, or in loop filtering
    m_usedSurfaces[0].push_back(id);

    if (!IsRegistered(id))
    {
        while (m_free_index_pool.empty() && (m_usedSurfaces.size() > 0))
        {
            // Evict the oldest BeginPicture/EndPicture set of surface IDs
            DDI_CHK_RET(RemoveLastHistoryElement(), "DDI_CODEC_RENDER_TARGET_TABLE::RemoveLastElement failed");
        }

        if (m_free_index_pool.empty())
        {
            return VA_STATUS_ERROR_OPERATION_FAILED;
        }

        m_va_to_rt_map[id] = m_free_index_pool.back();
        m_free_index_pool.pop_back();
    }

    return VA_STATUS_SUCCESS;
}

//!
//! \brief    Unregister Render Target Surface
//! \details  Unregister surface in render target table
//!
//! \param    [in] id
//!           VASurfaceID for the render target to be unregistered
//!
//! \return   VAStatus
//!           VA_STATUS_SUCCESS if successful, VA_STATUS_ERROR_INVALID_PARAMETER if
//!           no such surface is registered
//!
VAStatus DDI_CODEC_RENDER_TARGET_TABLE::UnRegisterRTSurface(VASurfaceID id)
{
    if (!IsRegistered(id))
    {
        DDI_VERBOSEMESSAGE("UnRegisterRTSurface: render target was not registered in the RTtbl!");
        return VA_STATUS_ERROR_INVALID_PARAMETER;
    }

    for(auto &vec: m_usedSurfaces)
    {
        vec.erase(std::remove(vec.begin(), vec.end(), id), vec.end());
    }

    m_free_index_pool.push_back(m_va_to_rt_map[id]);
    m_va_to_rt_map.erase(id);

    return VA_STATUS_SUCCESS;
}

//!
//! \brief    IsRegistered
//! \details  Determines whether or not a surface is registered in the render target table
//!
//! \param    [in] id
//!           VASurfaceID of the surface in question
//! \return   bool
//!           true if registered, false otherwise
//!
bool DDI_CODEC_RENDER_TARGET_TABLE::IsRegistered(VASurfaceID id) const
{
    return (m_va_to_rt_map.find(id) != m_va_to_rt_map.end());
}


//!
//! \brief    Set Current Render Target Surface
//! \details  Sets a registered VASurfaceID as the one currently being processed ("current")
//!
//! \param    [in] id
//!           VASurfaceID of the registered render target to be set as "current"
//!
//! \return   VAStatus
//!           VA_STATUS_SUCCESS if successful, VA_STATUS_ERROR_INVALID_PARAMETER if
//!           no such surface is registered

VAStatus DDI_CODEC_RENDER_TARGET_TABLE::SetCurrentRTSurface(VASurfaceID id)
{
    if (id != VA_INVALID_ID && (RegisterRTSurface(id) != VA_STATUS_SUCCESS))
    {
        return VA_STATUS_ERROR_INVALID_PARAMETER;
    }

    m_current_rt_surface = id;

    return VA_STATUS_SUCCESS;
}

//!
//! \brief    Get Current Render Target Surface
//! \details  Returns a VASurfaceID of the "current" render target
//!
//! \return   VASurfaceID
//!
VASurfaceID DDI_CODEC_RENDER_TARGET_TABLE::GetCurrentRTSurface() const
{
    return m_current_rt_surface;
}

//!
//! \brief    Set Current Reconstructed Frame Render Target Surface
//! \details  Sets a registered VASurfaceID as the one that should contain the reconstructed frame
//!
//! \param    [in] id
//!           VASurfaceID of the registered render target to be set as containing the reconstructed frame
//!
//! \return   VAStatus
//!           VA_STATUS_SUCCESS if successful, VA_STATUS_ERROR_INVALID_PARAMETER if
//!           no such surface is registered

VAStatus DDI_CODEC_RENDER_TARGET_TABLE::SetCurrentReconTarget(VASurfaceID id)
{
    if (RegisterRTSurface(id) != VA_STATUS_SUCCESS)
    {
        return VA_STATUS_ERROR_INVALID_PARAMETER;
    }

    m_current_recon_target = id;

    return VA_STATUS_SUCCESS;
}

//!
//! \brief    Get Current Reconstructed Frame Render Target Surface
//! \details  Returns a VASurfaceID of the reconstructed frame render target
//!
//! \return   VASurfaceID
//!
VASurfaceID DDI_CODEC_RENDER_TARGET_TABLE::GetCurrentReconTarget() const
{
    return m_current_recon_target;
}

//!
//! \brief    Get Registered VA IDs
//! \details  Returns a vector of VASurfaceIDs currently registered in the render target table
//!
//! \return   VASurfaceID
//!
std::vector<VASurfaceID> DDI_CODEC_RENDER_TARGET_TABLE::GetRegisteredVAIDs() const
{
    std::vector<VASurfaceID> retval;
    retval.reserve(m_va_to_rt_map.size());
    for (const auto& pair : m_va_to_rt_map)
    {
        retval.push_back(pair.first);
    }
    return retval;
}

//!
//! \brief    Get Num Render Targets
//! \details  Returns the number of registered render targets
//!
//! \return   size_t
//!
size_t DDI_CODEC_RENDER_TARGET_TABLE::GetNumRenderTargets() const
{
    return m_va_to_rt_map.size();
}

//!
//! \brief    Get Frame Index
//! \details  Returns a FrameIdx (driver internal surface management index)
//!           associated with the render target surface if it is registered in the table.
//!
//! \param    [in] id
//!           VASurfaceID of the registered render target
//!
//! \return   RTTableIdx
//!           FrameIdx of the render target with the VASurfaceID id if it is registered in the table,
//!           INVALID_RT_TABLE_INDEX if no such surface is registered
//!
RTTableIdx DDI_CODEC_RENDER_TARGET_TABLE::GetFrameIdx(VASurfaceID id)
{
    if (id == VA_INVALID_ID || !IsRegistered(id))
    {
        return INVALID_RT_TABLE_INDEX;
    }

    return m_va_to_rt_map[id];
}

//!
//! \brief    Get VA ID
//! \details  Returns a VASurfaceID to which the FrameIdx (driver internal surface management index)
//!           is assigned.
//!
//! \param    [in] FrameIdx
//!           FrameIdx of the render target
//!
//! \return   VASurfaceID
//!           VASurfaceID of the render target with the FrameIdx if it is registered in the table,
//!           VA_INVALID_ID if no such surface is registered
//!
VASurfaceID DDI_CODEC_RENDER_TARGET_TABLE::GetVAID(RTTableIdx FrameIdx) const
{
    using RTPair = std::pair<VASurfaceID, RTTableIdx>;
    VASurfaceID id = VA_INVALID_ID;

    auto it = std::find_if(m_va_to_rt_map.begin(), m_va_to_rt_map.end(),
        [=](const RTPair& pair){return pair.second == FrameIdx;});

    if (it != m_va_to_rt_map.end())
    {
        id = it->first;
    }

    return id;
}

VAStatus DDI_CODEC_RENDER_TARGET_TABLE::RemoveLastHistoryElement()
{
    std::vector<VASurfaceID> lastList = m_usedSurfaces.back();
    m_usedSurfaces.pop_back();

    std::set<VASurfaceID> surfaces;
    for (const auto &list: m_usedSurfaces)
    {
        surfaces.insert(list.begin(), list.end());
    }

    for (const auto &el: lastList)
    {
        bool unusedSurface = (surfaces.find(el) == surfaces.end());
        if (unusedSurface)
        {
            if (UnRegisterRTSurface(el) != VA_STATUS_SUCCESS)
            {
                return VA_STATUS_ERROR_OPERATION_FAILED;
            }
        }
    }
    return VA_STATUS_SUCCESS;
}

void DDI_CODEC_RENDER_TARGET_TABLE::BegeinPicture()
{
    if (m_usedSurfaces[0].size() > 0)
    {
        // maximum history length number of Begin/End picture calls it depends on async mode
        const size_t maxHistorySize = 20;
        m_usedSurfaces.insert(m_usedSurfaces.begin(), std::vector<VASurfaceID>());
        if (m_usedSurfaces.size() > maxHistorySize)
        {
            RemoveLastHistoryElement();
        }
    }
}

