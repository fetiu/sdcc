/* Register definitions for pic16f1455.
 * This file was automatically generated by:
 *   inc2h.pl
 *   Copyright (c) 2002, Kevin L. Pauba, All Rights Reserved
 */
#include <pic16f1455.h>

__sfr  __at (INDF0_ADDR)                   INDF0;
__sfr  __at (INDF1_ADDR)                   INDF1;
__sfr  __at (PCL_ADDR)                     PCL;
__sfr  __at (STATUS_ADDR)                  STATUS;
__sfr  __at (FSR0_ADDR)                    FSR0;
__sfr  __at (FSR0L_ADDR)                   FSR0L;
__sfr  __at (FSR0H_ADDR)                   FSR0H;
__sfr  __at (FSR1_ADDR)                    FSR1;
__sfr  __at (FSR1L_ADDR)                   FSR1L;
__sfr  __at (FSR1H_ADDR)                   FSR1H;
__sfr  __at (BSR_ADDR)                     BSR;
__sfr  __at (WREG_ADDR)                    WREG;
__sfr  __at (PCLATH_ADDR)                  PCLATH;
__sfr  __at (INTCON_ADDR)                  INTCON;
__sfr  __at (PORTA_ADDR)                   PORTA;
__sfr  __at (PORTC_ADDR)                   PORTC;
__sfr  __at (PIR1_ADDR)                    PIR1;
__sfr  __at (PIR2_ADDR)                    PIR2;
__sfr  __at (TMR0_ADDR)                    TMR0;
__sfr  __at (TMR1_ADDR)                    TMR1;
__sfr  __at (TMR1L_ADDR)                   TMR1L;
__sfr  __at (TMR1H_ADDR)                   TMR1H;
__sfr  __at (T1CON_ADDR)                   T1CON;
__sfr  __at (T1GCON_ADDR)                  T1GCON;
__sfr  __at (TMR2_ADDR)                    TMR2;
__sfr  __at (PR2_ADDR)                     PR2;
__sfr  __at (T2CON_ADDR)                   T2CON;
__sfr  __at (TRISA_ADDR)                   TRISA;
__sfr  __at (TRISC_ADDR)                   TRISC;
__sfr  __at (PIE1_ADDR)                    PIE1;
__sfr  __at (PIE2_ADDR)                    PIE2;
__sfr  __at (OPTION_REG_ADDR)              OPTION_REG;
__sfr  __at (PCON_ADDR)                    PCON;
__sfr  __at (WDTCON_ADDR)                  WDTCON;
__sfr  __at (OSCTUNE_ADDR)                 OSCTUNE;
__sfr  __at (OSCCON_ADDR)                  OSCCON;
__sfr  __at (OSCSTAT_ADDR)                 OSCSTAT;
__sfr  __at (ADRES_ADDR)                   ADRES;
__sfr  __at (ADRESL_ADDR)                  ADRESL;
__sfr  __at (ADRESH_ADDR)                  ADRESH;
__sfr  __at (ADCON0_ADDR)                  ADCON0;
__sfr  __at (ADCON1_ADDR)                  ADCON1;
__sfr  __at (ADCON2_ADDR)                  ADCON2;
__sfr  __at (LATA_ADDR)                    LATA;
__sfr  __at (LATC_ADDR)                    LATC;
__sfr  __at (CM1CON0_ADDR)                 CM1CON0;
__sfr  __at (CM1CON1_ADDR)                 CM1CON1;
__sfr  __at (CM2CON0_ADDR)                 CM2CON0;
__sfr  __at (CM2CON1_ADDR)                 CM2CON1;
__sfr  __at (CMOUT_ADDR)                   CMOUT;
__sfr  __at (BORCON_ADDR)                  BORCON;
__sfr  __at (FVRCON_ADDR)                  FVRCON;
__sfr  __at (DACCON0_ADDR)                 DACCON0;
__sfr  __at (DACCON1_ADDR)                 DACCON1;
__sfr  __at (APFCON_ADDR)                  APFCON;
__sfr  __at (ANSELA_ADDR)                  ANSELA;
__sfr  __at (ANSELC_ADDR)                  ANSELC;
__sfr  __at (PMADR_ADDR)                   PMADR;
__sfr  __at (PMADRL_ADDR)                  PMADRL;
__sfr  __at (PMADRH_ADDR)                  PMADRH;
__sfr  __at (PMDAT_ADDR)                   PMDAT;
__sfr  __at (PMDATL_ADDR)                  PMDATL;
__sfr  __at (PMDATH_ADDR)                  PMDATH;
__sfr  __at (PMCON1_ADDR)                  PMCON1;
__sfr  __at (PMCON2_ADDR)                  PMCON2;
__sfr  __at (VREGCON_ADDR)                 VREGCON;
__sfr  __at (RCREG_ADDR)                   RCREG;
__sfr  __at (TXREG_ADDR)                   TXREG;
__sfr  __at (SPBRGL_ADDR)                  SPBRGL;
__sfr  __at (SPBRGH_ADDR)                  SPBRGH;
__sfr  __at (RCSTA_ADDR)                   RCSTA;
__sfr  __at (TXSTA_ADDR)                   TXSTA;
__sfr  __at (BAUDCON_ADDR)                 BAUDCON;
__sfr  __at (WPUA_ADDR)                    WPUA;
__sfr  __at (SSP1BUF_ADDR)                 SSP1BUF;
__sfr  __at (SSPBUF_ADDR)                  SSPBUF;
__sfr  __at (SSP1ADD_ADDR)                 SSP1ADD;
__sfr  __at (SSPADD_ADDR)                  SSPADD;
__sfr  __at (SSP1MSK_ADDR)                 SSP1MSK;
__sfr  __at (SSPMSK_ADDR)                  SSPMSK;
__sfr  __at (SSP1STAT_ADDR)                SSP1STAT;
__sfr  __at (SSPSTAT_ADDR)                 SSPSTAT;
__sfr  __at (SSP1CON1_ADDR)                SSP1CON1;
__sfr  __at (SSPCON_ADDR)                  SSPCON;
__sfr  __at (SSPCON1_ADDR)                 SSPCON1;
__sfr  __at (SSP1CON2_ADDR)                SSP1CON2;
__sfr  __at (SSPCON2_ADDR)                 SSPCON2;
__sfr  __at (SSP1CON3_ADDR)                SSP1CON3;
__sfr  __at (SSPCON3_ADDR)                 SSPCON3;
__sfr  __at (IOCAP_ADDR)                   IOCAP;
__sfr  __at (IOCAN_ADDR)                   IOCAN;
__sfr  __at (IOCAF_ADDR)                   IOCAF;
__sfr  __at (CLKRCON_ADDR)                 CLKRCON;
__sfr  __at (CRCON_ADDR)                   CRCON;
__sfr  __at (PWM1DCL_ADDR)                 PWM1DCL;
__sfr  __at (PWM1DCH_ADDR)                 PWM1DCH;
__sfr  __at (PWM1CON_ADDR)                 PWM1CON;
__sfr  __at (PWM1CON0_ADDR)                PWM1CON0;
__sfr  __at (PWM2DCL_ADDR)                 PWM2DCL;
__sfr  __at (PWM2DCH_ADDR)                 PWM2DCH;
__sfr  __at (PWM2CON_ADDR)                 PWM2CON;
__sfr  __at (PWM2CON0_ADDR)                PWM2CON0;
__sfr  __at (CWG1DBR_ADDR)                 CWG1DBR;
__sfr  __at (CWG1DBF_ADDR)                 CWG1DBF;
__sfr  __at (CWG1CON0_ADDR)                CWG1CON0;
__sfr  __at (CWG1CON1_ADDR)                CWG1CON1;
__sfr  __at (CWG1CON2_ADDR)                CWG1CON2;
__sfr  __at (CRRC_ADDR)                    CRRC;
__sfr  __at (TST_CRRCL_ADDR)               TST_CRRCL;
__sfr  __at (TST_CRRCH_ADDR)               TST_CRRCH;
__sfr  __at (TST_CRLT_ADDR)                TST_CRLT;
__sfr  __at (UCON_ADDR)                    UCON;
__sfr  __at (UIR_ADDR)                     UIR;
__sfr  __at (USTAT_ADDR)                   USTAT;
__sfr  __at (UCFG_ADDR)                    UCFG;
__sfr  __at (UIE_ADDR)                     UIE;
__sfr  __at (UEIR_ADDR)                    UEIR;
__sfr  __at (UFRM_ADDR)                    UFRM;
__sfr  __at (UFRMH_ADDR)                   UFRMH;
__sfr  __at (UFRML_ADDR)                   UFRML;
__sfr  __at (UADDR_ADDR)                   UADDR;
__sfr  __at (UEIE_ADDR)                    UEIE;
__sfr  __at (UEP7_ADDR)                    UEP7;
__sfr  __at (UEP6_ADDR)                    UEP6;
__sfr  __at (UEP5_ADDR)                    UEP5;
__sfr  __at (UEP4_ADDR)                    UEP4;
__sfr  __at (UEP3_ADDR)                    UEP3;
__sfr  __at (UEP2_ADDR)                    UEP2;
__sfr  __at (UEP1_ADDR)                    UEP1;
__sfr  __at (UEP0_ADDR)                    UEP0;
__sfr  __at (ICDIO_ADDR)                   ICDIO;
__sfr  __at (ICDCON0_ADDR)                 ICDCON0;
__sfr  __at (ICDSTAT_ADDR)                 ICDSTAT;
__sfr  __at (DEVSEL_ADDR)                  DEVSEL;
__sfr  __at (ICDINSTL_ADDR)                ICDINSTL;
__sfr  __at (ICDINSTH_ADDR)                ICDINSTH;
__sfr  __at (ICDBK0CON_ADDR)               ICDBK0CON;
__sfr  __at (ICDBK0L_ADDR)                 ICDBK0L;
__sfr  __at (ICDBK0H_ADDR)                 ICDBK0H;
__sfr  __at (BSRICDSHAD_ADDR)              BSRICDSHAD;
__sfr  __at (STATUS_SHAD_ADDR)             STATUS_SHAD;
__sfr  __at (WREG_SHAD_ADDR)               WREG_SHAD;
__sfr  __at (BSR_SHAD_ADDR)                BSR_SHAD;
__sfr  __at (PCLATH_SHAD_ADDR)             PCLATH_SHAD;
__sfr  __at (FSR0L_SHAD_ADDR)              FSR0L_SHAD;
__sfr  __at (FSR0H_SHAD_ADDR)              FSR0H_SHAD;
__sfr  __at (FSR1L_SHAD_ADDR)              FSR1L_SHAD;
__sfr  __at (FSR1H_SHAD_ADDR)              FSR1H_SHAD;
__sfr  __at (STKPTR_ADDR)                  STKPTR;
__sfr  __at (TOSL_ADDR)                    TOSL;
__sfr  __at (TOSH_ADDR)                    TOSH;

// 
// bitfield definitions
// 
volatile __ADCON0bits_t __at(ADCON0_ADDR) ADCON0bits;
volatile __ADCON1bits_t __at(ADCON1_ADDR) ADCON1bits;
volatile __ADCON2bits_t __at(ADCON2_ADDR) ADCON2bits;
volatile __ANSELAbits_t __at(ANSELA_ADDR) ANSELAbits;
volatile __ANSELCbits_t __at(ANSELC_ADDR) ANSELCbits;
volatile __APFCONbits_t __at(APFCON_ADDR) APFCONbits;
volatile __BAUDCONbits_t __at(BAUDCON_ADDR) BAUDCONbits;
volatile __BORCONbits_t __at(BORCON_ADDR) BORCONbits;
volatile __BSRbits_t __at(BSR_ADDR) BSRbits;
volatile __CLKRCONbits_t __at(CLKRCON_ADDR) CLKRCONbits;
volatile __CM1CON0bits_t __at(CM1CON0_ADDR) CM1CON0bits;
volatile __CM1CON1bits_t __at(CM1CON1_ADDR) CM1CON1bits;
volatile __CM2CON0bits_t __at(CM2CON0_ADDR) CM2CON0bits;
volatile __CM2CON1bits_t __at(CM2CON1_ADDR) CM2CON1bits;
volatile __CMOUTbits_t __at(CMOUT_ADDR) CMOUTbits;
volatile __CRCONbits_t __at(CRCON_ADDR) CRCONbits;
volatile __CWG1CON0bits_t __at(CWG1CON0_ADDR) CWG1CON0bits;
volatile __CWG1CON1bits_t __at(CWG1CON1_ADDR) CWG1CON1bits;
volatile __CWG1CON2bits_t __at(CWG1CON2_ADDR) CWG1CON2bits;
volatile __CWG1DBFbits_t __at(CWG1DBF_ADDR) CWG1DBFbits;
volatile __CWG1DBRbits_t __at(CWG1DBR_ADDR) CWG1DBRbits;
volatile __DACCON0bits_t __at(DACCON0_ADDR) DACCON0bits;
volatile __DACCON1bits_t __at(DACCON1_ADDR) DACCON1bits;
volatile __DEVSELbits_t __at(DEVSEL_ADDR) DEVSELbits;
volatile __FVRCONbits_t __at(FVRCON_ADDR) FVRCONbits;
volatile __ICDBK0CONbits_t __at(ICDBK0CON_ADDR) ICDBK0CONbits;
volatile __ICDBK0Hbits_t __at(ICDBK0H_ADDR) ICDBK0Hbits;
volatile __ICDBK0Lbits_t __at(ICDBK0L_ADDR) ICDBK0Lbits;
volatile __ICDCON0bits_t __at(ICDCON0_ADDR) ICDCON0bits;
volatile __ICDINSTHbits_t __at(ICDINSTH_ADDR) ICDINSTHbits;
volatile __ICDINSTLbits_t __at(ICDINSTL_ADDR) ICDINSTLbits;
volatile __ICDIObits_t __at(ICDIO_ADDR) ICDIObits;
volatile __ICDSTATbits_t __at(ICDSTAT_ADDR) ICDSTATbits;
volatile __INTCONbits_t __at(INTCON_ADDR) INTCONbits;
volatile __IOCAFbits_t __at(IOCAF_ADDR) IOCAFbits;
volatile __IOCANbits_t __at(IOCAN_ADDR) IOCANbits;
volatile __IOCAPbits_t __at(IOCAP_ADDR) IOCAPbits;
volatile __LATAbits_t __at(LATA_ADDR) LATAbits;
volatile __LATCbits_t __at(LATC_ADDR) LATCbits;
volatile __OPTION_REGbits_t __at(OPTION_REG_ADDR) OPTION_REGbits;
volatile __OSCCONbits_t __at(OSCCON_ADDR) OSCCONbits;
volatile __OSCSTATbits_t __at(OSCSTAT_ADDR) OSCSTATbits;
volatile __OSCTUNEbits_t __at(OSCTUNE_ADDR) OSCTUNEbits;
volatile __PCONbits_t __at(PCON_ADDR) PCONbits;
volatile __PIE1bits_t __at(PIE1_ADDR) PIE1bits;
volatile __PIE2bits_t __at(PIE2_ADDR) PIE2bits;
volatile __PIR1bits_t __at(PIR1_ADDR) PIR1bits;
volatile __PIR2bits_t __at(PIR2_ADDR) PIR2bits;
volatile __PMCON1bits_t __at(PMCON1_ADDR) PMCON1bits;
volatile __PORTAbits_t __at(PORTA_ADDR) PORTAbits;
volatile __PORTCbits_t __at(PORTC_ADDR) PORTCbits;
volatile __PWM1CONbits_t __at(PWM1CON_ADDR) PWM1CONbits;
volatile __PWM1CON0bits_t __at(PWM1CON0_ADDR) PWM1CON0bits;
volatile __PWM1DCHbits_t __at(PWM1DCH_ADDR) PWM1DCHbits;
volatile __PWM1DCLbits_t __at(PWM1DCL_ADDR) PWM1DCLbits;
volatile __PWM2CONbits_t __at(PWM2CON_ADDR) PWM2CONbits;
volatile __PWM2CON0bits_t __at(PWM2CON0_ADDR) PWM2CON0bits;
volatile __PWM2DCHbits_t __at(PWM2DCH_ADDR) PWM2DCHbits;
volatile __PWM2DCLbits_t __at(PWM2DCL_ADDR) PWM2DCLbits;
volatile __RCSTAbits_t __at(RCSTA_ADDR) RCSTAbits;
volatile __SSP1CON1bits_t __at(SSP1CON1_ADDR) SSP1CON1bits;
volatile __SSP1CON2bits_t __at(SSP1CON2_ADDR) SSP1CON2bits;
volatile __SSP1CON3bits_t __at(SSP1CON3_ADDR) SSP1CON3bits;
volatile __SSP1STATbits_t __at(SSP1STAT_ADDR) SSP1STATbits;
volatile __SSPCONbits_t __at(SSPCON_ADDR) SSPCONbits;
volatile __SSPCON1bits_t __at(SSPCON1_ADDR) SSPCON1bits;
volatile __SSPCON2bits_t __at(SSPCON2_ADDR) SSPCON2bits;
volatile __SSPCON3bits_t __at(SSPCON3_ADDR) SSPCON3bits;
volatile __SSPSTATbits_t __at(SSPSTAT_ADDR) SSPSTATbits;
volatile __STATUSbits_t __at(STATUS_ADDR) STATUSbits;
volatile __STATUS_SHADbits_t __at(STATUS_SHAD_ADDR) STATUS_SHADbits;
volatile __T1CONbits_t __at(T1CON_ADDR) T1CONbits;
volatile __T1GCONbits_t __at(T1GCON_ADDR) T1GCONbits;
volatile __T2CONbits_t __at(T2CON_ADDR) T2CONbits;
volatile __TRISAbits_t __at(TRISA_ADDR) TRISAbits;
volatile __TRISCbits_t __at(TRISC_ADDR) TRISCbits;
volatile __TXSTAbits_t __at(TXSTA_ADDR) TXSTAbits;
volatile __UADDRbits_t __at(UADDR_ADDR) UADDRbits;
volatile __UCFGbits_t __at(UCFG_ADDR) UCFGbits;
volatile __UCONbits_t __at(UCON_ADDR) UCONbits;
volatile __UEIEbits_t __at(UEIE_ADDR) UEIEbits;
volatile __UEIRbits_t __at(UEIR_ADDR) UEIRbits;
volatile __UEP0bits_t __at(UEP0_ADDR) UEP0bits;
volatile __UEP1bits_t __at(UEP1_ADDR) UEP1bits;
volatile __UEP2bits_t __at(UEP2_ADDR) UEP2bits;
volatile __UEP3bits_t __at(UEP3_ADDR) UEP3bits;
volatile __UEP4bits_t __at(UEP4_ADDR) UEP4bits;
volatile __UEP5bits_t __at(UEP5_ADDR) UEP5bits;
volatile __UEP6bits_t __at(UEP6_ADDR) UEP6bits;
volatile __UEP7bits_t __at(UEP7_ADDR) UEP7bits;
volatile __UFRMHbits_t __at(UFRMH_ADDR) UFRMHbits;
volatile __UFRMLbits_t __at(UFRML_ADDR) UFRMLbits;
volatile __UIEbits_t __at(UIE_ADDR) UIEbits;
volatile __UIRbits_t __at(UIR_ADDR) UIRbits;
volatile __USTATbits_t __at(USTAT_ADDR) USTATbits;
volatile __VREGCONbits_t __at(VREGCON_ADDR) VREGCONbits;
volatile __WDTCONbits_t __at(WDTCON_ADDR) WDTCONbits;
volatile __WPUAbits_t __at(WPUA_ADDR) WPUAbits;

