/*
* Copyright (c) 2017, Intel Corporation
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
//! \file     media_ddi_base.h
//! \brief    Defines base class for DDI media encode/decoder/VP
//!

#ifndef _MEDIA_DDI_BASE_H_
#define _MEDIA_DDI_BASE_H_

#include <stdint.h>
#include <va/va.h>
#include <va/va_backend.h>

#include "media_libva.h"
#include "media_libva_util.h"

//!
//! \class  DdiMediaBase
//! \brief  Ddi media base class
//!
class DdiMediaBase
{
public:
    //!
    //! \brief Constructor
    //!
    DdiMediaBase(){};

    //!
    //! \brief Destructor
    //!
    virtual ~DdiMediaBase(){};

    //!
    //! \brief    Get ready to process for a target surface
    //! \details  It begins the process (encode/decode/vp) for a specified target surface
    //!
    //! \param    [in] ctx
    //!           Pointer to VA driver context
    //! \param    [in] context
    //!           Already created context for the process
    //! \param    [in] renderTarget
    //!           Specified target surface
    //!
    //! \return   VAStatus
    //!           VA_STATUS_SUCCESS if success, else fail reason
    //!
    virtual VAStatus BeginPicture(
        VADriverContextP ctx,
        VAContextID      context,
        VASurfaceID      renderTarget) = 0;

    //!
    //! \brief    Send required buffers to for process
    //! \details  It sends needed buffers by the process (encode/decode/vp) to the driver
    //!
    //! \param    [in] ctx
    //!           Pointer to VA driver context
    //! \param    [in] context
    //!           Already created context for the process
    //! \param    [in] buffers
    //!           Pointer to the buffer array
    //! \param    [in] numBuffers
    //!           Number of buffers in above array
    //!
    //! \return   VAStatus
    //!           VA_STATUS_SUCCESS if success, else fail reason
    //!
    virtual VAStatus RenderPicture(
        VADriverContextP ctx,
        VAContextID      context,
        VABufferID       *buffers,
        int32_t          numBuffers) = 0;

    //!
    //! \brief    Make the end of rendering for a picture
    //! \details  The driver will start processing the corresponding decoding/encoding/vp for
    //!           given context. This call is non-blocking. The app can start another
    //!           Begin/Render/End sequence on a different render target
    //!
    //! \param    [in] ctx
    //!           Pointer to VA driver context
    //! \param    [in] context
    //!           Already created context for the process
    //!
    //! \return   VAStatus
    //!           VA_STATUS_SUCCESS if success, else fail reason
    //!
    virtual VAStatus EndPicture(
        VADriverContextP ctx,
        VAContextID      context) = 0;

};

#endif /*  _MEDIA_DDI_BASE_H_ */
