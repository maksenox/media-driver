L0:
         mov (8|M0)               r13.0<1>:ud   0x0:ud                          
         mov (1|M0)               r22.4<1>:ud   0x1000100:ud                    
         mov (4|M0)               acc0.0<1>:w   0x6420:v                        
         add (4|M0)               acc0.0<1>:w   acc0.0<4;4,1>:w   0x40:uw         
         shl (4|M0)               r22.0<1>:w    acc0.0<4;4,1>:w   0x5:uw          
(W&~f0.1) jmpi                                L1600                           
L96:
         mov (8|M0)               acc0.0<1>:f   r25.3<0;1,0>:f                  
         mac (1|M0)               r23.3<1>:f    r25.5<0;1,0>:f    15.0:f          
         cmp (1|M0)    (eq)f1.0   null.0<1>:w   r24.2<0;1,0>:ub   0x1:uw          
(f1.0)   mov (1|M0)               acc0.3<1>:f   r23.3<0;1,0>:f                  
(f1.0)   mac (1|M0)               r23.3<1>:f    r24.1<0;1,0>:f    -2.0:f          
         mov (4|M0)               r10.0<1>:f    0x5054585C:vf                   
         mov (4|M0)               r10.4<1>:f    0x304048:vf                     
         mov (8|M0)               r13.0<1>:ud   r0.0<8;8,1>:ud                  
         mov (2|M0)               r13.0<1>:ud   0x0:ud                          
         mov (1|M0)               r13.2<1>:ud   0x0:ud                          
         add (1|M0)               a0.0<1>:ud    r23.5<0;1,0>:ud   0xA8C0100:ud    
         mov (8|M0)               acc0.0<1>:f   r23.3<0;1,0>:f                  
         mac (8|M0)               r16.0<1>:f    r25.5<0;1,0>:f    r10.7<0;1,0>:f  
         mac (8|M0)               r17.0<1>:f    r25.5<0;1,0>:f    -1.0:f          
         mov (8|M0)               acc0.0<1>:f   r25.2<0;1,0>:f                  
         mac (8|M0)               r14.0<1>:f    r25.4<0;1,0>:f    r10.0<8;8,1>:f  
         mac (8|M0)               r15.0<1>:f    r25.4<0;1,0>:f    r10.0<8;8,1>:f  
         mul (8|M0)               acc0.0<1>:f   r25.4<0;1,0>:f    8.0:f           
         add (8|M0)               r14.0<1>:f    acc0.0<8;8,1>:f   r14.0<8;8,1>:f  
         add (8|M0)               r15.0<1>:f    acc0.0<8;8,1>:f   r15.0<8;8,1>:f  
         send (16|M0)             r72:uw   r13:ub  0x2       a0.0      
         mul (8|M0)               acc0.0<1>:f   r25.5<0;1,0>:f    -2.0:f          
         add (8|M0)               r16.0<1>:f    acc0.0<8;8,1>:f   r16.0<8;8,1>:f  
         add (8|M0)               r17.0<1>:f    acc0.0<8;8,1>:f   r17.0<8;8,1>:f  
         mul (16|M0)              acc0.0<1>:f   r72.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r64.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r74.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r66.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r76.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r68.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r78.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r70.0<1>:ud  acc0.0<8;8,1>:f             
         mov (16|M0)              r64.0<1>:uw   r64.0<16;8,2>:uw                
         mov (16|M0)              r66.0<1>:uw   r66.0<16;8,2>:uw                
         mov (16|M0)              r68.0<1>:uw   r68.0<16;8,2>:uw                
         mov (16|M0)              r70.0<1>:uw   r70.0<16;8,2>:uw                
         send (16|M0)             r72:uw   r13:ub  0x2       a0.0      
         mul (8|M0)               acc0.0<1>:f   r25.5<0;1,0>:f    2.0:f           
         add (8|M0)               r16.0<1>:f    acc0.0<8;8,1>:f   r16.0<8;8,1>:f  
         add (8|M0)               r17.0<1>:f    acc0.0<8;8,1>:f   r17.0<8;8,1>:f  
         mov (8|M0)               acc0.0<1>:f   r14.0<8;8,1>:f                  
         mac (8|M0)               r14.0<1>:f    r25.4<0;1,0>:f    -8.0:f          
         mov (8|M0)               acc0.0<1>:f   r15.0<8;8,1>:f                  
         mac (8|M0)               r15.0<1>:f    r25.4<0;1,0>:f    -8.0:f          
         mul (16|M0)              acc0.0<1>:f   r72.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r72.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r74.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r74.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r76.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r76.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r78.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r78.0<1>:ud  acc0.0<8;8,1>:f             
         mov (16|M0)              r65.0<1>:uw   r72.0<16;8,2>:uw                
         mov (16|M0)              r67.0<1>:uw   r74.0<16;8,2>:uw                
         mov (16|M0)              r69.0<1>:uw   r76.0<16;8,2>:uw                
         mov (16|M0)              r71.0<1>:uw   r78.0<16;8,2>:uw                
         send (16|M0)             r72:uw   r13:ub  0x2       a0.0      
         mul (8|M0)               acc0.0<1>:f   r25.5<0;1,0>:f    -2.0:f          
         add (8|M0)               r16.0<1>:f    acc0.0<8;8,1>:f   r16.0<8;8,1>:f  
         add (8|M0)               r17.0<1>:f    acc0.0<8;8,1>:f   r17.0<8;8,1>:f  
         mul (16|M0)              acc0.0<1>:f   r72.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r72.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r74.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r74.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r76.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r76.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r78.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r78.0<1>:ud  acc0.0<8;8,1>:f             
         mov (16|M0)              r18.0<1>:uw   r72.0<16;8,2>:uw                
         mov (16|M0)              r10.0<1>:uw   r74.0<16;8,2>:uw                
         mov (16|M0)              r11.0<1>:uw   r76.0<16;8,2>:uw                
         mov (16|M0)              r12.0<1>:uw   r78.0<16;8,2>:uw                
         send (16|M0)             r72:uw   r13:ub  0x2       a0.0      
         mul (16|M0)              acc0.0<1>:f   r72.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r72.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r74.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r74.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r76.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r76.0<1>:ud  acc0.0<8;8,1>:f             
         mul (16|M0)              acc0.0<1>:f   r78.0<8;8,1>:f    65280.0:f       
         mov (16|M0)              (sat)r78.0<1>:ud  acc0.0<8;8,1>:f             
         mov (16|M0)              r73.0<1>:uw   r72.0<16;8,2>:uw                
         mov (16|M0)              r75.0<1>:uw   r74.0<16;8,2>:uw                
         mov (16|M0)              r77.0<1>:uw   r76.0<16;8,2>:uw                
         mov (16|M0)              r79.0<1>:uw   r78.0<16;8,2>:uw                
         mov (16|M0)              r72.0<1>:uw   r18.0<16;16,1>:uw               
         mov (16|M0)              r74.0<1>:uw   r10.0<16;16,1>:uw               
         mov (16|M0)              r76.0<1>:uw   r11.0<16;16,1>:uw               
         mov (16|M0)              r78.0<1>:uw   r12.0<16;16,1>:uw               
         mov (1|M0)               a0.8<1>:uw    0x800:uw                        
         mov (1|M0)               a0.9<1>:uw    0x840:uw                        
         mov (1|M0)               a0.10<1>:uw   0x880:uw                        
         mov (1|M0)               a0.11<1>:uw   0x8C0:uw                        
         add (4|M0)               a0.12<1>:uw   a0.8<4;4,1>:uw    0x100:uw        
L1600:
         nop                    
         illegal                
         illegal                
         illegal                
         illegal                
         illegal                
         illegal                
         illegal                
         illegal                
