/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996-1998 Microsoft Corporation

Module Name:

    emul.h

Abstract:

    Prototypes for special-case fast Blt functions for display drivers to use.


-------------------------------------------------------------------*/

#ifndef __EMUL_H__
#define __EMUL_H__

#include <gpe.h>

class Emulator : public GPE
{

public:

    /////////////////////////////////////////////
    //                                         //
    //              2bpp Methods               //
    //                                         //
    /////////////////////////////////////////////

    //
    // Sourceless blts
    //
    SCODE EmulatedBltFill02     ( GPEBltParms * );
    SCODE EmulatedBltDstInvert02( GPEBltParms * );
    SCODE EmulatedBltPatInvert02( GPEBltParms * );

    //
    // Sourced blts
    //
    SCODE EmulatedBltSrcCopy0202  ( GPEBltParms * );
    SCODE EmulatedBltSrcAnd0202   ( GPEBltParms * );
    SCODE EmulatedBltSrcPaint0202 ( GPEBltParms * );
    SCODE EmulatedBltSrcInvert0202( GPEBltParms * );

    //
    // Text expansion
    //
    SCODE EmulatedBltText02     ( GPEBltParms * );

    /////////////////////////////////////////////
    //                                         //
    //              8bpp Methods               //
    //                                         //
    /////////////////////////////////////////////

    //
    // Sourceless blts
    //
    SCODE EmulatedBltFill08     ( GPEBltParms * );
    SCODE EmulatedBltDstInvert08( GPEBltParms * );
    SCODE EmulatedBltPatInvert08( GPEBltParms * );

    //
    // Sourced blts
    //
    SCODE EmulatedBltSrcCopy0808( GPEBltParms * );
    SCODE EmulatedBltSrcAnd0808( GPEBltParms * );
    SCODE EmulatedBltSrcPaint0808( GPEBltParms * );
    SCODE EmulatedBltSrcInvert0808( GPEBltParms * );

    //
    // Text expansion
    //
    SCODE EmulatedBltText08     ( GPEBltParms * );

    /////////////////////////////////////////////
    //                                         //
    //              16bpp Methods              //
    //                                         //
    /////////////////////////////////////////////

    //
    // Sourceless blts
    //
    SCODE EmulatedBltFill16     ( GPEBltParms * );

    //
    // Sourced blts
    //
    SCODE EmulatedBltSrcCopy1616( GPEBltParms * );
    SCODE EmulatedBltSrcAnd1616( GPEBltParms * );
    SCODE EmulatedBltSrcPaint1616( GPEBltParms * );
    SCODE EmulatedBltSrcInvert1616( GPEBltParms * );

    //
    // Text expansion
    //
    SCODE EmulatedBltText16         ( GPEBltParms * );
    SCODE EmulatedBltAlphaText16    ( GPEBltParms * );
    SCODE EmulatedBltAlphaText02    ( GPEBltParms * );

};

#endif __EMUL_H__
