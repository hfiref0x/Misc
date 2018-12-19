#pragma once

#define _IOffset(Class, itf)         ((UINT_PTR)&(((Class *)0)->itf))
#define IToClass(Class, itf, pitf)   ((Class  *)(((LPSTR)pitf)-_IOffset(Class, itf)))
#define IToClassN(Class, itf, pitf)  IToClass(Class, itf, pitf)

typedef HRESULT(CALLBACK *LPFNCREATEINSTANCE)(IUnknown *pUnkOuter, REFIID riid, void **ppvObject);

typedef struct _CClassFactory {
    const IClassFactoryVtbl *cf;
    const CLSID *pclsid;
    LPFNCREATEINSTANCE lpfnCreateInstance;
} CClassFactory, *PCClassFactory;

#define AMSI_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
     EXTERN_C const GUID DECLSPEC_SELECTANY name \
            = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }

AMSI_DEFINE_GUID(CLSID_AmsiProvider, 0x1c0643e1, 0x5b0a, 0x4420, 0x9b, 0x76, 0x0d, 0xe9, 0x26, 0x4b, 0x4c, 0x59);
AMSI_DEFINE_GUID(IID_AntimalwareProvider, 0xb2cabfe3, 0xfe04, 0x42b1, 0xa5, 0xdf, 0x08, 0xd4, 0x83, 0xd4, 0xd1, 0x25);


STDAPI_(LONG) DllAddRef();
STDAPI_(LONG) DllRelease();

extern const CClassFactory g_clsmap[];
