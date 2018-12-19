

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for AmsiScan.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AmsiScan_i_h__
#define __AmsiScan_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAmsiProvider_FWD_DEFINED__
#define __IAmsiProvider_FWD_DEFINED__
typedef interface IAmsiProvider IAmsiProvider;

#endif 	/* __IAmsiProvider_FWD_DEFINED__ */


#ifndef __AmsiProvider_FWD_DEFINED__
#define __AmsiProvider_FWD_DEFINED__

#ifdef __cplusplus
typedef class AmsiProvider AmsiProvider;
#else
typedef struct AmsiProvider AmsiProvider;
#endif /* __cplusplus */

#endif 	/* __AmsiProvider_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAmsiProvider_INTERFACE_DEFINED__
#define __IAmsiProvider_INTERFACE_DEFINED__

/* interface IAmsiProvider */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAmsiProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05025dfe-70d5-4b61-a55a-aa21585d4cb2")
    IAmsiProvider : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IAmsiProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAmsiProvider * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAmsiProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAmsiProvider * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAmsiProvider * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAmsiProvider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAmsiProvider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAmsiProvider * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IAmsiProviderVtbl;

    interface IAmsiProvider
    {
        CONST_VTBL struct IAmsiProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAmsiProvider_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAmsiProvider_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAmsiProvider_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAmsiProvider_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAmsiProvider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAmsiProvider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAmsiProvider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAmsiProvider_INTERFACE_DEFINED__ */



#ifndef __AmsiScanLib_LIBRARY_DEFINED__
#define __AmsiScanLib_LIBRARY_DEFINED__

/* library AmsiScanLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AmsiScanLib;

EXTERN_C const CLSID CLSID_AmsiProvider;

#ifdef __cplusplus

class DECLSPEC_UUID("1c0643e1-5b0a-4420-9b76-0de9264b4c59")
AmsiProvider;
#endif
#endif /* __AmsiScanLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


