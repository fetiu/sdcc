/* Register definitions for pic12f629.
 * This file was automatically generated by:
 *   inc2h.pl V4850
 *   Copyright (c) 2002, Kevin L. Pauba, All Rights Reserved
 */
#include <pic12f629.h>

__sfr  __at (INDF_ADDR)                    INDF;
__sfr  __at (TMR0_ADDR)                    TMR0;
__sfr  __at (PCL_ADDR)                     PCL;
__sfr  __at (STATUS_ADDR)                  STATUS;
__sfr  __at (FSR_ADDR)                     FSR;
__sfr  __at (GPIO_ADDR)                    GPIO;
__sfr  __at (PCLATH_ADDR)                  PCLATH;
__sfr  __at (INTCON_ADDR)                  INTCON;
__sfr  __at (PIR1_ADDR)                    PIR1;
__sfr  __at (TMR1L_ADDR)                   TMR1L;
__sfr  __at (TMR1H_ADDR)                   TMR1H;
__sfr  __at (T1CON_ADDR)                   T1CON;
__sfr  __at (CMCON_ADDR)                   CMCON;
__sfr  __at (OPTION_REG_ADDR)              OPTION_REG;
__sfr  __at (TRISIO_ADDR)                  TRISIO;
__sfr  __at (PIE1_ADDR)                    PIE1;
__sfr  __at (PCON_ADDR)                    PCON;
__sfr  __at (OSCCAL_ADDR)                  OSCCAL;
__sfr  __at (WPU_ADDR)                     WPU;
__sfr  __at (IOCB_ADDR)                    IOCB;
__sfr  __at (IOC_ADDR)                     IOC;
__sfr  __at (VRCON_ADDR)                   VRCON;
__sfr  __at (EEDATA_ADDR)                  EEDATA;
__sfr  __at (EEDAT_ADDR)                   EEDAT;
__sfr  __at (EEADR_ADDR)                   EEADR;
__sfr  __at (EECON1_ADDR)                  EECON1;
__sfr  __at (EECON2_ADDR)                  EECON2;

// 
// bitfield definitions
// 
volatile __CMCONbits_t __at(CMCON_ADDR) CMCONbits;
volatile __EECON1bits_t __at(EECON1_ADDR) EECON1bits;
volatile __GPIObits_t __at(GPIO_ADDR) GPIObits;
volatile __INTCONbits_t __at(INTCON_ADDR) INTCONbits;
volatile __IOCbits_t __at(IOC_ADDR) IOCbits;
volatile __IOCBbits_t __at(IOCB_ADDR) IOCBbits;
volatile __OPTION_REGbits_t __at(OPTION_REG_ADDR) OPTION_REGbits;
volatile __OSCCALbits_t __at(OSCCAL_ADDR) OSCCALbits;
volatile __PCONbits_t __at(PCON_ADDR) PCONbits;
volatile __PIE1bits_t __at(PIE1_ADDR) PIE1bits;
volatile __PIR1bits_t __at(PIR1_ADDR) PIR1bits;
volatile __STATUSbits_t __at(STATUS_ADDR) STATUSbits;
volatile __T1CONbits_t __at(T1CON_ADDR) T1CONbits;
volatile __VRCONbits_t __at(VRCON_ADDR) VRCONbits;

