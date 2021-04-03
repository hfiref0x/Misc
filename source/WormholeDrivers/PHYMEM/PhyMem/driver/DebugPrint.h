//////////////////////////////////////////////////////////////////////////////
//	Copyright © 1998,1999 PHD Computer Consultants Ltd
//	DebugPrint code header to add to a test driver
//
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C"
{
#endif

#define DEBUGPRINT 0	// Set to 1 to do DebugPrints in free version

/////////////////////////////////////////////////////////////////////////////

#if DBG || DEBUGPRINT
#define DODEBUGPRINT 1
#else
#define DODEBUGPRINT 0
#endif

#if DODEBUGPRINT

void DebugPrintInit(char*);
void DebugPrintClose();
void DebugPrintMsg(char*);

#else

#define DebugPrintInit(x)
#define DebugPrintClose()
#define DebugPrintMsg(x)

#endif

void DebugPrint2(int max, const char *format, ... );
void DebugPrint(const char *format, ... );

/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
