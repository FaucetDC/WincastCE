/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

macros.h

Abstract:  

Notes: 


--*/
#ifndef MACROS_H
#define MACROS_H

#define RELEASE(x)		do { if(x) (x)->Release(); } while (0)
#define RELEASEN(x) 	do { if(x) {(x)->Release(); x=NULL; }} while (0)
#define ADDREF(x) 		do { if(x) (x)->AddRef(); } while (0)
#define ASSIGN(l,r) 	do { if ((l)=(r)) (l)->AddRef(); } while (0)
#define ASSIGNNZ(l,r) 	do { (l)=(r); (l)->AddRef(); } while (0)
#define CALL2(x)  		do { if (FAILED(hr=(x))) return hr;  } while (0)
#define CALL(x) 		do { if (FAILED(hr=(x))) goto errRtn;} while (0)
#define CALLSTRICT(x) 	do { if (NOERROR !=(hr=(x))) goto errRtn;} while (0)

/*
#define VDATEPTROUT(p, type) if (IsBadWritePtrP((p), sizeof(type)))\
	return (ResultFromScode(E_INVALIDARG));
#define VDATEPTROUTCB(p, cb) if (IsBadWritePtrP((p), cb))\
	return (ResultFromScode(E_INVALIDARG));
#define VDATEPTRIN(p, type) if (IsBadReadPtrP((p), sizeof(type)))\
	return (ResultFromScode(E_INVALIDARG));
#define VDATEPTRINCB(p, cb) if (IsBadReadPtrP((p), cb))\
	return (ResultFromScode(E_INVALIDARG));
*/


/* Ensure that the out pointer returned from a method call matches its hresult
 * according to the COM rules.
 */
#define ASSERTOUTIFACE(hr, p) \
		ASSERT ((SUCCEEDED(hr) && (p)) || (FAILED(hr) && (p) == NULL))

	
/* The following macro implements the first three methods of a class that 
 * inherits directly from its interface class, i.e., does not use nested 
 * classes.  Therefore it only supports one interface.
 */
#define UNKNOWN_IMPL(class, interface) \
STDMETHODIMP class::QueryInterface (REFIID riid, PVOID * ppObj)	\
{\
  	if ((riid == IID_IUnknown) || (riid == IID_##interface)) {\
	    *ppObj = (PVOID)(interface *)this;\
  		AddRef();\
		return NOERROR;\
	} else {\
		*ppObj = NULL;\
		return E_NOINTERFACE;\
	}\
}\
\
STDMETHODIMP_(ULONG) class::AddRef (void)\
{   return InterlockedIncrement(&m_cRef); }\
\
STDMETHODIMP_(ULONG) class::Release (void)\
{\
	if (0 == InterlockedDecrement(&m_cRef)) {\
		delete this;\
		return 0;\
	}\
	return m_cRef;\
}

#pragma warning (disable:4355)

#define NC(a,b) a##::##b
#define DECLARE_NC(a,b) friend b;

/*
 *      The following macro declares a nested class CUnknownImpl,
 *      creates an object of that class in the outer class, and
 *      declares CUnknownImpl to be a friend of the outer class. 
 */
#define STDUNKDECL(classname ) \
	struct CUnknownImpl:IUnknown \
	{ public: \
    CUnknownImpl( C##classname  * p##classname ) { m_p##classname = p##classname;} \
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, PVOID * ppvObj); \
    STDMETHOD_(ULONG,AddRef)(THIS); \
    STDMETHOD_(ULONG,Release)(THIS); \
    private: C##classname * m_p##classname; }; \
    DECLARE_NC(C##classname, CUnknownImpl) \
    CUnknownImpl m_Unknown;

// Same as above, but the back pointer is named "This"	
#define STDUNK_DECL(classname ) \
	struct CUnknownImpl:IUnknown \
	{ public: \
    CUnknownImpl( C##classname  * p##classname ) { This = p##classname;} \
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, PVOID * ppvObj); \
    STDMETHOD_(ULONG,AddRef)(THIS); \
    STDMETHOD_(ULONG,Release)(THIS); \
    private: C##classname * This; }; \
    DECLARE_NC(C##classname, CUnknownImpl) \
    CUnknownImpl m_Unknown;


/*
 *      The following macro implements all the methods of a nested
 *      CUnknownImpl class EXCEPT FOR QUERYINTERFACE.  This macro was
 *      written after about 20 classes were written in which the
 *      implementations of CUnknownImpl were all the same.
 */
#define STDUNKIMPL(classname) \
STDMETHODIMP_(ULONG) NC(C##classname,CUnknownImpl)::AddRef( void ){ \
    return ++m_p##classname->m_cRef; } \
STDMETHODIMP_(ULONG) NC(C##classname,CUnknownImpl)::Release( void ){ \
    if (--m_p##classname->m_cRef == 0) { delete m_p##classname; return 0; } \
    return m_p##classname->m_cRef;}

// Same as above, but the back pointer is named "This"	
#define STDUNK_IMPL(classname) \
STDMETHODIMP_(ULONG) NC(C##classname,CUnknownImpl)::AddRef( void ){ \
    return ++This->m_cRef; } \
STDMETHODIMP_(ULONG) NC(C##classname,CUnknownImpl)::Release( void ){ \
    if (--This->m_cRef == 0) { delete This; return 0; } \
    return This->m_cRef;}

/*
 *      The following macro implements class::CUnknownImpl::QueryInterface IN
 *      THE SPECIAL CASE IN WHICH THE OUTER CLASS PRESENTS ONLY ONE INTERFACE
 *      OTHER THAN IUNKNOWN.  This is not universally the case,
 *      but it is common enough that this macro will save time and space.
 */
#define STDUNK_QI_IMPL(classname, interfacename) \
STDMETHODIMP NC(C##classname,CUnknownImpl)::QueryInterface \
    (REFIID iidInterface, void  *  * ppv) { \
    if (iidInterface == IID_IUnknown) {\
        *ppv = (void  *)&This->m_Unknown;\
        AddRef(); return NOERROR;\
    } else if (iidInterface == IID_I##interfacename) { \
        *ppv = (void  *) &(This->m_##classname); \
        This->m_punkOuter->AddRef(); return NOERROR; \
    } else \
        {*ppv = NULL; return ResultFromScode(E_NOINTERFACE);} \
}


/*
 *      The following macro implements the IUnknown methods inherited
 *      by the implementation of another interface.  The implementation
 *      is simply to delegate all calls to m_punkOuter.  Parameters:
 *      ocname is the outer class name, icname is the implementation
 *      class name.
 *      
 */
#define STDUNKIMPL_FORDERIVED(ocname, icname) \
STDMETHODIMP NC(C##ocname,C##icname)::QueryInterface \
(REFIID iidInterface, PVOID * ppvObj) { \
    return m_p##ocname->m_punkOuter->QueryInterface(iidInterface, ppvObj);} \
STDMETHODIMP_(ULONG) NC(C##ocname,C##icname)::AddRef(void) { \
    return m_p##ocname->m_punkOuter->AddRef(); } \
STDMETHODIMP_(ULONG) NC(C##ocname,C##icname)::Release(void) { \
    return m_p##ocname->m_punkOuter->Release(); }

// Same as above, but the back pointer is named "This"	
#define STDUNK_IMPL_FORDERIVED(ocname, icname) \
STDMETHODIMP NC(C##ocname,C##icname)::QueryInterface \
(REFIID iidInterface, PVOID * ppvObj) { \
    return This->m_punkOuter->QueryInterface(iidInterface, ppvObj);} \
STDMETHODIMP_(ULONG) NC(C##ocname,C##icname)::AddRef(void) { \
    return This->m_punkOuter->AddRef(); } \
STDMETHODIMP_(ULONG) NC(C##ocname,C##icname)::Release(void) { \
    return This->m_punkOuter->Release(); }
	
	
#define STDUNK_PROTOTYPES \
		STDMETHOD (QueryInterface) (THIS_ REFIID riid, PVOID * ppvObj) ; \
    	STDMETHOD_(ULONG,AddRef) (THIS)  ; \
    	STDMETHOD_(ULONG,Release) (THIS) ; \

#define IUNKNOWN_XFUNCS	"RdI", "Uu", "Uu"
#define IMPURE	/* empty */


/* Same as STDMETHOD but not virtual.  Used for private methods not
 * part of a COM interface. 
 */
#define PRIVMETHOD(method)       HRESULT STDMETHODCALLTYPE method
#define PRIVMETHOD_(type,method) type STDMETHODCALLTYPE method
#define PRIVMETHODIMP  STDMETHODIMP
#define PRIVMETHODIMP_ STDMETHODIMP_


#endif // MACROS_H
