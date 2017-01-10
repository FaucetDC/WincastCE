
/*
 * $Log:   P:/user/amir/lite/vcs/stdcomp.h_v  $

      Rev 1.9   25 Feb 1998 16:05:04   Yair
   Added WinCE components

      Rev 1.8   16 Dec 1997 11:40:52   ANDRY
   host address range to search for DiskOnChip window is a parameter of the
   registration routine of DiskOnChip socket component

      Rev 1.7   12 Nov 1997  8:35:00   ANDRY
   added DiskOnChip 2000 socket component for Elan SC400 x86 board

      Rev 1.6   07 Oct 1997 14:59:04   ANDRY
   IRQ parameter for flRegisterElanPCIC()

      Rev 1.5   06 Oct 1997  9:21:04   ANDRY
   added socket components for VME-177 and COBUX boards

      Rev 1.4   31 Aug 1997 14:24:00   danig
   Registration routines return status

      Rev 1.3   28 Aug 1997 16:37:00   danig
   IRQ received as PCIC registration parameter

      Rev 1.2   25 Aug 1997 12:01:18   ANDRY
   New standard components:
           RFA socket component for AMD Elan SC400 board
           PCIC socket component for AMD Elan SC400 board
           16-bit AMD MTD

      Rev 1.1   18 Aug 1997 15:49:00   danig
   PCIC registration routine receives window base address

      Rev 1.0   07 Jul 1997 15:24:04   amirban
   Initial revision.
 */

/************************************************************************/
/*                                                                      */
/*		FAT-FTL Lite Software Development Kit			*/
/*              Copyright (C) M-Systems Ltd. 1995-1998                  */
/*									*/
/************************************************************************/

#ifndef STDCOMP_H
#define STDCOMP_H

#include "flstatus.h"

/*----------------------------------------------------------------------*/
/*    Registration routines for MTDs supplied with FLite		*/
/*----------------------------------------------------------------------*/

FLStatus    flRegisterI28F008(void);                  /* see I28F008.C  */
FLStatus    flRegisterI28F016(void);                  /* see I28F016.C  */
FLStatus    flRegisterAMDMTD(void);                   /* see AMDMTD.C   */
FLStatus    flRegisterWAMDMTD(void);                  /* see WAMDMTD.C  */
FLStatus    flRegisterCDSN(void);                     /* see NFDC2048.C */
FLStatus    flRegisterCFISCS(void);                   /* see CFISCS.C   */
FLStatus    flRegisterDOC2000(void); 	              /* see NFDC2148.C */


/*----------------------------------------------------------------------*/
/*    Registration routines for socket I/F supplied with FLite		*/
/*----------------------------------------------------------------------*/

FLStatus    flRegisterPCIC(unsigned int, unsigned int, unsigned char);
						      /* see PCIC.C     */
FLStatus    flRegisterElanPCIC(unsigned int, unsigned int, unsigned char);
                                                      /* see PCICELAN.C */
FLStatus    flRegisterLFDC(void);                     /* see LFDC.C     */
FLStatus    flRegisterDOCSOC(unsigned long, unsigned long);
                                                      /* see DOCSOC.C */
FLStatus    flRegisterElanRFASocket (int, int);       /* see ELRFASOC.C */
FLStatus    flRegisterElanDocSocket (long, long, int);/* see ELDOCSOC.C */
FLStatus    flRegisterVME177rfaSocket (unsigned long, unsigned long);
                                                      /* FLVME177.C */
FLStatus    flRegisterCobuxSocket (void);             /* see COBUXSOC.C */
FLStatus    flRegisterCEDOCSOC(void);                 /* see CEDOCSOC.C */
FLStatus    flRegisterCS(void);                       /* see CSwinCE.C */

/*----------------------------------------------------------------------*/
/*    Registration routines for translation layers supplied with FLite	*/
/*----------------------------------------------------------------------*/

FLStatus    flRegisterFTL(void);                      /* see FTLLITE.C  */
FLStatus    flRegisterNFTL(void);                     /* see NFTLLITE.C */
FLStatus    flRegisterSSFDC(void);                    /* see SSFDC.C    */

/*----------------------------------------------------------------------*/
/*    	    Component registration routine in CUSTOM.C			*/
/*----------------------------------------------------------------------*/

void	    flRegisterComponents(void);

#endif /* STDCOMP_H */