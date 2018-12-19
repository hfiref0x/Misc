// dllmain.h : Declaration of module class.

class CAmsiScanModule : public ATL::CAtlDllModuleT< CAmsiScanModule >
{
public :
	DECLARE_LIBID(LIBID_AmsiScanLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_AMSISCAN, "{508c88ef-ca97-4107-a022-6025892ef192}")
};

extern class CAmsiScanModule _AtlModule;
