/* MACHINE GENERATED, DO NOT EDIT */
#define KUSER_SHARED_SYSCALL 7FFE0300h

__declspec(naked) ULONG NTAPI NtGdiAbortDoc()
{
    __asm {
        mov eax, 00001000h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAbortPath()
{
    __asm {
        mov eax, 00001001h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAddFontResourceW()
{
    __asm {
        mov eax, 00001002h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAddRemoteFontToDC()
{
    __asm {
        mov eax, 00001003h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAddFontMemResourceEx()
{
    __asm {
        mov eax, 00001004h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRemoveMergeFont()
{
    __asm {
        mov eax, 00001005h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAddRemoteMMInstanceToDC()
{
    __asm {
        mov eax, 00001006h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiAlphaBlend()
{
    __asm {
        mov eax, 00001007h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000030h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAngleArc()
{
    __asm {
        mov eax, 00001008h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAnyLinkedFonts()
{
    __asm {
        mov eax, 00001009h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFontIsLinked()
{
    __asm {
        mov eax, 0000100Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiArcInternal()
{
    __asm {
        mov eax, 0000100Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000028h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBeginPath()
{
    __asm {
        mov eax, 0000100Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBitBlt()
{
    __asm {
        mov eax, 0000100Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiCancelDC()
{
    __asm {
        mov eax, 0000100Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCheckBitmapBits()
{
    __asm {
        mov eax, 0000100Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCloseFigure()
{
    __asm {
        mov eax, 00001010h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiClearBitmapAttributes()
{
    __asm {
        mov eax, 00001011h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiClearBrushAttributes()
{
    __asm {
        mov eax, 00001012h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiColorCorrectPalette()
{
    __asm {
        mov eax, 00001013h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCombineRgn()
{
    __asm {
        mov eax, 00001014h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCombineTransform()
{
    __asm {
        mov eax, 00001015h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiComputeXformCoefficients()
{
    __asm {
        mov eax, 00001016h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiConsoleTextOut()
{
    __asm {
        mov eax, 00001017h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiConvertMetafileRect()
{
    __asm {
        mov eax, 00001018h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateBitmap()
{
    __asm {
        mov eax, 00001019h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateClientObj()
{
    __asm {
        mov eax, 0000101Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateColorSpace()
{
    __asm {
        mov eax, 0000101Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateColorTransform()
{
    __asm {
        mov eax, 0000101Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateCompatibleBitmap()
{
    __asm {
        mov eax, 0000101Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateCompatibleDC()
{
    __asm {
        mov eax, 0000101Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateDIBBrush()
{
    __asm {
        mov eax, 0000101Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateDIBitmapInternal()
{
    __asm {
        mov eax, 00001020h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateDIBSection()
{
    __asm {
        mov eax, 00001021h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000024h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateEllipticRgn()
{
    __asm {
        mov eax, 00001022h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateHalftonePalette()
{
    __asm {
        mov eax, 00001023h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateHatchBrushInternal()
{
    __asm {
        mov eax, 00001024h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateMetafileDC()
{
    __asm {
        mov eax, 00001025h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreatePaletteInternal()
{
    __asm {
        mov eax, 00001026h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreatePatternBrushInternal()
{
    __asm {
        mov eax, 00001027h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreatePen()
{
    __asm {
        mov eax, 00001028h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateRectRgn()
{
    __asm {
        mov eax, 00001029h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateRoundRectRgn()
{
    __asm {
        mov eax, 0000102Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateServerMetaFile()
{
    __asm {
        mov eax, 0000102Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCreateSolidBrush()
{
    __asm {
        mov eax, 0000102Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiD3dContextCreate()
{
    __asm {
        mov eax, 0000102Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiD3dContextDestroy()
{
    __asm {
        mov eax, 0000102Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiD3dContextDestroyAll()
{
    __asm {
        mov eax, 0000102Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiD3dValidateTextureStageState()
{
    __asm {
        mov eax, 00001030h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiD3dDrawPrimitives2()
{
    __asm {
        mov eax, 00001031h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetDriverState()
{
    __asm {
        mov eax, 00001032h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdAddAttachedSurface()
{
    __asm {
        mov eax, 00001033h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdAlphaBlt()
{
    __asm {
        mov eax, 00001034h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdAttachSurface()
{
    __asm {
        mov eax, 00001035h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdBeginMoCompFrame()
{
    __asm {
        mov eax, 00001036h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdBlt()
{
    __asm {
        mov eax, 00001037h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCanCreateSurface()
{
    __asm {
        mov eax, 00001038h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCanCreateD3DBuffer()
{
    __asm {
        mov eax, 00001039h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdColorControl()
{
    __asm {
        mov eax, 0000103Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCreateDirectDrawObject()
{
    __asm {
        mov eax, 0000103Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCreateSurface()
{
    __asm {
        mov eax, 0000103Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCreateD3DBuffer()
{
    __asm {
        mov eax, 0000103Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCreateMoComp()
{
    __asm {
        mov eax, 0000103Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCreateSurfaceObject()
{
    __asm {
        mov eax, 0000103Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDeleteDirectDrawObject()
{
    __asm {
        mov eax, 00001040h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDeleteSurfaceObject()
{
    __asm {
        mov eax, 00001041h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDestroyMoComp()
{
    __asm {
        mov eax, 00001042h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDestroySurface()
{
    __asm {
        mov eax, 00001043h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDestroyD3DBuffer()
{
    __asm {
        mov eax, 00001044h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdEndMoCompFrame()
{
    __asm {
        mov eax, 00001045h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdFlip()
{
    __asm {
        mov eax, 00001046h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdFlipToGDISurface()
{
    __asm {
        mov eax, 00001047h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetAvailDriverMemory()
{
    __asm {
        mov eax, 00001048h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetBltStatus()
{
    __asm {
        mov eax, 00001049h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetDC()
{
    __asm {
        mov eax, 0000104Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetDriverInfo()
{
    __asm {
        mov eax, 0000104Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetDxHandle()
{
    __asm {
        mov eax, 0000104Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetFlipStatus()
{
    __asm {
        mov eax, 0000104Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetInternalMoCompInfo()
{
    __asm {
        mov eax, 0000104Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetMoCompBuffInfo()
{
    __asm {
        mov eax, 0000104Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetMoCompGuids()
{
    __asm {
        mov eax, 00001050h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetMoCompFormats()
{
    __asm {
        mov eax, 00001051h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdGetScanLine()
{
    __asm {
        mov eax, 00001052h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdLock()
{
    __asm {
        mov eax, 00001053h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdLockD3D()
{
    __asm {
        mov eax, 00001054h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdQueryDirectDrawObject()
{
    __asm {
        mov eax, 00001055h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdQueryMoCompStatus()
{
    __asm {
        mov eax, 00001056h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdReenableDirectDrawObject()
{
    __asm {
        mov eax, 00001057h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdReleaseDC()
{
    __asm {
        mov eax, 00001058h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdRenderMoComp()
{
    __asm {
        mov eax, 00001059h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdResetVisrgn()
{
    __asm {
        mov eax, 0000105Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdSetColorKey()
{
    __asm {
        mov eax, 0000105Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdSetExclusiveMode()
{
    __asm {
        mov eax, 0000105Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdSetGammaRamp()
{
    __asm {
        mov eax, 0000105Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdCreateSurfaceEx()
{
    __asm {
        mov eax, 0000105Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdSetOverlayPosition()
{
    __asm {
        mov eax, 0000105Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdUnattachSurface()
{
    __asm {
        mov eax, 00001060h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdUnlock()
{
    __asm {
        mov eax, 00001061h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdUnlockD3D()
{
    __asm {
        mov eax, 00001062h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdUpdateOverlay()
{
    __asm {
        mov eax, 00001063h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdWaitForVerticalBlank()
{
    __asm {
        mov eax, 00001064h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpCanCreateVideoPort()
{
    __asm {
        mov eax, 00001065h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpColorControl()
{
    __asm {
        mov eax, 00001066h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpCreateVideoPort()
{
    __asm {
        mov eax, 00001067h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpDestroyVideoPort()
{
    __asm {
        mov eax, 00001068h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpFlipVideoPort()
{
    __asm {
        mov eax, 00001069h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortBandwidth()
{
    __asm {
        mov eax, 0000106Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortField()
{
    __asm {
        mov eax, 0000106Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortFlipStatus()
{
    __asm {
        mov eax, 0000106Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortInputFormats()
{
    __asm {
        mov eax, 0000106Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortLine()
{
    __asm {
        mov eax, 0000106Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortOutputFormats()
{
    __asm {
        mov eax, 0000106Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoPortConnectInfo()
{
    __asm {
        mov eax, 00001070h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpGetVideoSignalStatus()
{
    __asm {
        mov eax, 00001071h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpUpdateVideoPort()
{
    __asm {
        mov eax, 00001072h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpWaitForVideoPortSync()
{
    __asm {
        mov eax, 00001073h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpAcquireNotification()
{
    __asm {
        mov eax, 00001074h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDvpReleaseNotification()
{
    __asm {
        mov eax, 00001075h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDxgGenericThunk()
{
    __asm {
        mov eax, 00001076h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDeleteClientObj()
{
    __asm {
        mov eax, 00001077h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDeleteColorSpace()
{
    __asm {
        mov eax, 00001078h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDeleteColorTransform()
{
    __asm {
        mov eax, 00001079h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDeleteObjectApp()
{
    __asm {
        mov eax, 0000107Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDescribePixelFormat()
{
    __asm {
        mov eax, 0000107Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetPerBandInfo()
{
    __asm {
        mov eax, 0000107Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDoBanding()
{
    __asm {
        mov eax, 0000107Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDoPalette()
{
    __asm {
        mov eax, 0000107Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDrawEscape()
{
    __asm {
        mov eax, 0000107Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEllipse()
{
    __asm {
        mov eax, 00001080h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEnableEudc()
{
    __asm {
        mov eax, 00001081h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEndDoc()
{
    __asm {
        mov eax, 00001082h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEndPage()
{
    __asm {
        mov eax, 00001083h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEndPath()
{
    __asm {
        mov eax, 00001084h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEnumFontChunk()
{
    __asm {
        mov eax, 00001085h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEnumFontClose()
{
    __asm {
        mov eax, 00001086h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEnumFontOpen()
{
    __asm {
        mov eax, 00001087h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEnumObjects()
{
    __asm {
        mov eax, 00001088h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEqualRgn()
{
    __asm {
        mov eax, 00001089h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEudcLoadUnloadLink()
{
    __asm {
        mov eax, 0000108Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiExcludeClipRect()
{
    __asm {
        mov eax, 0000108Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtCreatePen()
{
    __asm {
        mov eax, 0000108Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtCreateRegion()
{
    __asm {
        mov eax, 0000108Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtEscape()
{
    __asm {
        mov eax, 0000108Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtFloodFill()
{
    __asm {
        mov eax, 0000108Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtGetObjectW()
{
    __asm {
        mov eax, 00001090h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtSelectClipRgn()
{
    __asm {
        mov eax, 00001091h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiExtTextOutW()
{
    __asm {
        mov eax, 00001092h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000024h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFillPath()
{
    __asm {
        mov eax, 00001093h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFillRgn()
{
    __asm {
        mov eax, 00001094h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiFlattenPath()
{
    __asm {
        mov eax, 00001095h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFlush()
{
    __asm {
        mov eax, 00001096h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtGdiForceUFIMapping()
{
    __asm {
        mov eax, 00001097h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFrameRgn()
{
    __asm {
        mov eax, 00001098h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFullscreenControl()
{
    __asm {
        mov eax, 00001099h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetAndSetDCDword()
{
    __asm {
        mov eax, 0000109Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetAppClipBox()
{
    __asm {
        mov eax, 0000109Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetBitmapBits()
{
    __asm {
        mov eax, 0000109Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetBitmapDimension()
{
    __asm {
        mov eax, 0000109Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetBoundsRect()
{
    __asm {
        mov eax, 0000109Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetCharABCWidthsW()
{
    __asm {
        mov eax, 0000109Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetCharacterPlacementW()
{
    __asm {
        mov eax, 000010A0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetCharSet()
{
    __asm {
        mov eax, 000010A1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetCharWidthW()
{
    __asm {
        mov eax, 000010A2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetCharWidthInfo()
{
    __asm {
        mov eax, 000010A3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetColorAdjustment()
{
    __asm {
        mov eax, 000010A4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetColorSpaceforBitmap()
{
    __asm {
        mov eax, 000010A5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDCDword()
{
    __asm {
        mov eax, 000010A6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDCforBitmap()
{
    __asm {
        mov eax, 000010A7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDCObject()
{
    __asm {
        mov eax, 000010A8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDCPoint()
{
    __asm {
        mov eax, 000010A9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDeviceCaps()
{
    __asm {
        mov eax, 000010AAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDeviceGammaRamp()
{
    __asm {
        mov eax, 000010ABh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDeviceCapsAll()
{
    __asm {
        mov eax, 000010ACh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDIBitsInternal()
{
    __asm {
        mov eax, 000010ADh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000024h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetETM()
{
    __asm {
        mov eax, 000010AEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetEudcTimeStampEx()
{
    __asm {
        mov eax, 000010AFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetFontData()
{
    __asm {
        mov eax, 000010B0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetFontResourceInfoInternalW()
{
    __asm {
        mov eax, 000010B1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetGlyphIndicesW()
{
    __asm {
        mov eax, 000010B2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetGlyphIndicesWInternal()
{
    __asm {
        mov eax, 000010B3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetGlyphOutline()
{
    __asm {
        mov eax, 000010B4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetKerningPairs()
{
    __asm {
        mov eax, 000010B5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetLinkedUFIs()
{
    __asm {
        mov eax, 000010B6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetMiterLimit()
{
    __asm {
        mov eax, 000010B7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetMonitorID()
{
    __asm {
        mov eax, 000010B8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetNearestColor()
{
    __asm {
        mov eax, 000010B9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetNearestPaletteIndex()
{
    __asm {
        mov eax, 000010BAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetObjectBitmapHandle()
{
    __asm {
        mov eax, 000010BBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetOutlineTextMetricsInternalW()
{
    __asm {
        mov eax, 000010BCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetPath()
{
    __asm {
        mov eax, 000010BDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetPixel()
{
    __asm {
        mov eax, 000010BEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetRandomRgn()
{
    __asm {
        mov eax, 000010BFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetRasterizerCaps()
{
    __asm {
        mov eax, 000010C0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetRealizationInfo()
{
    __asm {
        mov eax, 000010C1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetRegionData()
{
    __asm {
        mov eax, 000010C2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetRgnBox()
{
    __asm {
        mov eax, 000010C3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetServerMetaFileBits()
{
    __asm {
        mov eax, 000010C4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetSpoolMessage()
{
    __asm {
        mov eax, 000010C5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetStats()
{
    __asm {
        mov eax, 000010C6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetStockObject()
{
    __asm {
        mov eax, 000010C7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetStringBitmapW()
{
    __asm {
        mov eax, 000010C8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetSystemPaletteUse()
{
    __asm {
        mov eax, 000010C9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetTextCharsetInfo()
{
    __asm {
        mov eax, 000010CAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetTextExtent()
{
    __asm {
        mov eax, 000010CBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetTextExtentExW()
{
    __asm {
        mov eax, 000010CCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetTextFaceW()
{
    __asm {
        mov eax, 000010CDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetTextMetricsW()
{
    __asm {
        mov eax, 000010CEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetTransform()
{
    __asm {
        mov eax, 000010CFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetUFI()
{
    __asm {
        mov eax, 000010D0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetEmbUFI()
{
    __asm {
        mov eax, 000010D1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetUFIPathname()
{
    __asm {
        mov eax, 000010D2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000028h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetEmbedFonts()
{
    __asm {
        mov eax, 000010D3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtGdiChangeGhostFont()
{
    __asm {
        mov eax, 000010D4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiAddEmbFontToDC()
{
    __asm {
        mov eax, 000010D5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetFontUnicodeRanges()
{
    __asm {
        mov eax, 000010D6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetWidthTable()
{
    __asm {
        mov eax, 000010D7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGradientFill()
{
    __asm {
        mov eax, 000010D8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiHfontCreate()
{
    __asm {
        mov eax, 000010D9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiIcmBrushInfo()
{
    __asm {
        mov eax, 000010DAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiInit()
{
    __asm {
        mov eax, 000010DBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtGdiInitSpool()
{
    __asm {
        mov eax, 000010DCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtGdiIntersectClipRect()
{
    __asm {
        mov eax, 000010DDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiInvertRgn()
{
    __asm {
        mov eax, 000010DEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiLineTo()
{
    __asm {
        mov eax, 000010DFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiMakeFontDir()
{
    __asm {
        mov eax, 000010E0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiMakeInfoDC()
{
    __asm {
        mov eax, 000010E1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiMaskBlt()
{
    __asm {
        mov eax, 000010E2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000034h
    }
}

__declspec(naked) ULONG NTAPI NtGdiModifyWorldTransform()
{
    __asm {
        mov eax, 000010E3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiMonoBitmap()
{
    __asm {
        mov eax, 000010E4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiMoveTo()
{
    __asm {
        mov eax, 000010E5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiOffsetClipRgn()
{
    __asm {
        mov eax, 000010E6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiOffsetRgn()
{
    __asm {
        mov eax, 000010E7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiOpenDCW()
{
    __asm {
        mov eax, 000010E8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiPatBlt()
{
    __asm {
        mov eax, 000010E9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPolyPatBlt()
{
    __asm {
        mov eax, 000010EAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPathToRegion()
{
    __asm {
        mov eax, 000010EBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPlgBlt()
{
    __asm {
        mov eax, 000010ECh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiPolyDraw()
{
    __asm {
        mov eax, 000010EDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPolyPolyDraw()
{
    __asm {
        mov eax, 000010EEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPolyTextOutW()
{
    __asm {
        mov eax, 000010EFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPtInRegion()
{
    __asm {
        mov eax, 000010F0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiPtVisible()
{
    __asm {
        mov eax, 000010F1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiQueryFonts()
{
    __asm {
        mov eax, 000010F2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiQueryFontAssocInfo()
{
    __asm {
        mov eax, 000010F3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRectangle()
{
    __asm {
        mov eax, 000010F4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRectInRegion()
{
    __asm {
        mov eax, 000010F5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRectVisible()
{
    __asm {
        mov eax, 000010F6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRemoveFontResourceW()
{
    __asm {
        mov eax, 000010F7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRemoveFontMemResourceEx()
{
    __asm {
        mov eax, 000010F8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiResetDC()
{
    __asm {
        mov eax, 000010F9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiResizePalette()
{
    __asm {
        mov eax, 000010FAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRestoreDC()
{
    __asm {
        mov eax, 000010FBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiRoundRect()
{
    __asm {
        mov eax, 000010FCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSaveDC()
{
    __asm {
        mov eax, 000010FDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiScaleViewportExtEx()
{
    __asm {
        mov eax, 000010FEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiScaleWindowExtEx()
{
    __asm {
        mov eax, 000010FFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSelectBitmap()
{
    __asm {
        mov eax, 00001100h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSelectBrush()
{
    __asm {
        mov eax, 00001101h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSelectClipPath()
{
    __asm {
        mov eax, 00001102h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSelectFont()
{
    __asm {
        mov eax, 00001103h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSelectPen()
{
    __asm {
        mov eax, 00001104h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetBitmapAttributes()
{
    __asm {
        mov eax, 00001105h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetBitmapBits()
{
    __asm {
        mov eax, 00001106h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetBitmapDimension()
{
    __asm {
        mov eax, 00001107h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetBoundsRect()
{
    __asm {
        mov eax, 00001108h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetBrushAttributes()
{
    __asm {
        mov eax, 00001109h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetBrushOrg()
{
    __asm {
        mov eax, 0000110Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetColorAdjustment()
{
    __asm {
        mov eax, 0000110Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetColorSpace()
{
    __asm {
        mov eax, 0000110Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetDeviceGammaRamp()
{
    __asm {
        mov eax, 0000110Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetDIBitsToDeviceInternal()
{
    __asm {
        mov eax, 0000110Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000040h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetFontEnumeration()
{
    __asm {
        mov eax, 0000110Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetFontXform()
{
    __asm {
        mov eax, 00001110h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetIcmMode()
{
    __asm {
        mov eax, 00001111h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetLinkedUFIs()
{
    __asm {
        mov eax, 00001112h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetMagicColors()
{
    __asm {
        mov eax, 00001113h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetMetaRgn()
{
    __asm {
        mov eax, 00001114h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetMiterLimit()
{
    __asm {
        mov eax, 00001115h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDeviceWidth()
{
    __asm {
        mov eax, 00001116h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiMirrorWindowOrg()
{
    __asm {
        mov eax, 00001117h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetLayout()
{
    __asm {
        mov eax, 00001118h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetPixel()
{
    __asm {
        mov eax, 00001119h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetPixelFormat()
{
    __asm {
        mov eax, 0000111Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetRectRgn()
{
    __asm {
        mov eax, 0000111Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetSystemPaletteUse()
{
    __asm {
        mov eax, 0000111Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetTextJustification()
{
    __asm {
        mov eax, 0000111Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetupPublicCFONT()
{
    __asm {
        mov eax, 0000111Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetVirtualResolution()
{
    __asm {
        mov eax, 0000111Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetSizeDevice()
{
    __asm {
        mov eax, 00001120h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiStartDoc()
{
    __asm {
        mov eax, 00001121h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiStartPage()
{
    __asm {
        mov eax, 00001122h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiStretchBlt()
{
    __asm {
        mov eax, 00001123h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000030h
    }
}

__declspec(naked) ULONG NTAPI NtGdiStretchDIBitsInternal()
{
    __asm {
        mov eax, 00001124h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000040h
    }
}

__declspec(naked) ULONG NTAPI NtGdiStrokeAndFillPath()
{
    __asm {
        mov eax, 00001125h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiStrokePath()
{
    __asm {
        mov eax, 00001126h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSwapBuffers()
{
    __asm {
        mov eax, 00001127h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiTransformPoints()
{
    __asm {
        mov eax, 00001128h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiTransparentBlt()
{
    __asm {
        mov eax, 00001129h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiUnloadPrinterDriver()
{
    __asm {
        mov eax, 0000112Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiUnmapMemFont()
{
    __asm {
        mov eax, 0000112Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiUnrealizeObject()
{
    __asm {
        mov eax, 0000112Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiUpdateColors()
{
    __asm {
        mov eax, 0000112Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiWidenPath()
{
    __asm {
        mov eax, 0000112Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserActivateKeyboardLayout()
{
    __asm {
        mov eax, 0000112Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserAlterWindowStyle()
{
    __asm {
        mov eax, 00001130h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserAssociateInputContext()
{
    __asm {
        mov eax, 00001131h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserAttachThreadInput()
{
    __asm {
        mov eax, 00001132h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserBeginPaint()
{
    __asm {
        mov eax, 00001133h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserBitBltSysBmp()
{
    __asm {
        mov eax, 00001134h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtUserBlockInput()
{
    __asm {
        mov eax, 00001135h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserBuildHimcList()
{
    __asm {
        mov eax, 00001136h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserBuildHwndList()
{
    __asm {
        mov eax, 00001137h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserBuildNameList()
{
    __asm {
        mov eax, 00001138h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserBuildPropList()
{
    __asm {
        mov eax, 00001139h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallHwnd()
{
    __asm {
        mov eax, 0000113Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallHwndLock()
{
    __asm {
        mov eax, 0000113Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallHwndOpt()
{
    __asm {
        mov eax, 0000113Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallHwndParam()
{
    __asm {
        mov eax, 0000113Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserCallHwndParamLock()
{
    __asm {
        mov eax, 0000113Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserCallMsgFilter()
{
    __asm {
        mov eax, 0000113Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallNextHookEx()
{
    __asm {
        mov eax, 00001140h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallNoParam()
{
    __asm {
        mov eax, 00001141h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallOneParam()
{
    __asm {
        mov eax, 00001142h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCallTwoParam()
{
    __asm {
        mov eax, 00001143h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserChangeClipboardChain()
{
    __asm {
        mov eax, 00001144h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserChangeDisplaySettings()
{
    __asm {
        mov eax, 00001145h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserCheckImeHotKey()
{
    __asm {
        mov eax, 00001146h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCheckMenuItem()
{
    __asm {
        mov eax, 00001147h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserChildWindowFromPointEx()
{
    __asm {
        mov eax, 00001148h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserClipCursor()
{
    __asm {
        mov eax, 00001149h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserCloseClipboard()
{
    __asm {
        mov eax, 0000114Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserCloseDesktop()
{
    __asm {
        mov eax, 0000114Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserCloseWindowStation()
{
    __asm {
        mov eax, 0000114Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserConsoleControl()
{
    __asm {
        mov eax, 0000114Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserConvertMemHandle()
{
    __asm {
        mov eax, 0000114Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCopyAcceleratorTable()
{
    __asm {
        mov eax, 0000114Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserCountClipboardFormats()
{
    __asm {
        mov eax, 00001150h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateAcceleratorTable()
{
    __asm {
        mov eax, 00001151h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateCaret()
{
    __asm {
        mov eax, 00001152h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateDesktop()
{
    __asm {
        mov eax, 00001153h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateInputContext()
{
    __asm {
        mov eax, 00001154h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateLocalMemHandle()
{
    __asm {
        mov eax, 00001155h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateWindowEx()
{
    __asm {
        mov eax, 00001156h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000003Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserCreateWindowStation()
{
    __asm {
        mov eax, 00001157h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDdeGetQualityOfService()
{
    __asm {
        mov eax, 00001158h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDdeInitialize()
{
    __asm {
        mov eax, 00001159h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserDdeSetQualityOfService()
{
    __asm {
        mov eax, 0000115Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDeferWindowPos()
{
    __asm {
        mov eax, 0000115Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtUserDefSetText()
{
    __asm {
        mov eax, 0000115Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserDeleteMenu()
{
    __asm {
        mov eax, 0000115Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDestroyAcceleratorTable()
{
    __asm {
        mov eax, 0000115Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserDestroyCursor()
{
    __asm {
        mov eax, 0000115Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserDestroyInputContext()
{
    __asm {
        mov eax, 00001160h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserDestroyMenu()
{
    __asm {
        mov eax, 00001161h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserDestroyWindow()
{
    __asm {
        mov eax, 00001162h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserDisableThreadIme()
{
    __asm {
        mov eax, 00001163h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserDispatchMessage()
{
    __asm {
        mov eax, 00001164h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserDragDetect()
{
    __asm {
        mov eax, 00001165h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDragObject()
{
    __asm {
        mov eax, 00001166h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserDrawAnimatedRects()
{
    __asm {
        mov eax, 00001167h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserDrawCaption()
{
    __asm {
        mov eax, 00001168h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserDrawCaptionTemp()
{
    __asm {
        mov eax, 00001169h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDrawIconEx()
{
    __asm {
        mov eax, 0000116Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserDrawMenuBarTemp()
{
    __asm {
        mov eax, 0000116Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserEmptyClipboard()
{
    __asm {
        mov eax, 0000116Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserEnableMenuItem()
{
    __asm {
        mov eax, 0000116Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserEnableScrollBar()
{
    __asm {
        mov eax, 0000116Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserEndDeferWindowPosEx()
{
    __asm {
        mov eax, 0000116Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserEndMenu()
{
    __asm {
        mov eax, 00001170h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserEndPaint()
{
    __asm {
        mov eax, 00001171h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserEnumDisplayDevices()
{
    __asm {
        mov eax, 00001172h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserEnumDisplayMonitors()
{
    __asm {
        mov eax, 00001173h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserEnumDisplaySettings()
{
    __asm {
        mov eax, 00001174h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserEvent()
{
    __asm {
        mov eax, 00001175h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserExcludeUpdateRgn()
{
    __asm {
        mov eax, 00001176h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserFillWindow()
{
    __asm {
        mov eax, 00001177h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserFindExistingCursorIcon()
{
    __asm {
        mov eax, 00001178h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserFindWindowEx()
{
    __asm {
        mov eax, 00001179h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserFlashWindowEx()
{
    __asm {
        mov eax, 0000117Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetAltTabInfo()
{
    __asm {
        mov eax, 0000117Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetAncestor()
{
    __asm {
        mov eax, 0000117Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetAppImeLevel()
{
    __asm {
        mov eax, 0000117Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetAsyncKeyState()
{
    __asm {
        mov eax, 0000117Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetAtomName()
{
    __asm {
        mov eax, 0000117Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetCaretBlinkTime()
{
    __asm {
        mov eax, 00001180h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetCaretPos()
{
    __asm {
        mov eax, 00001181h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClassInfo()
{
    __asm {
        mov eax, 00001182h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClassName()
{
    __asm {
        mov eax, 00001183h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClipboardData()
{
    __asm {
        mov eax, 00001184h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClipboardFormatName()
{
    __asm {
        mov eax, 00001185h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClipboardOwner()
{
    __asm {
        mov eax, 00001186h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClipboardSequenceNumber()
{
    __asm {
        mov eax, 00001187h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClipboardViewer()
{
    __asm {
        mov eax, 00001188h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetClipCursor()
{
    __asm {
        mov eax, 00001189h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetComboBoxInfo()
{
    __asm {
        mov eax, 0000118Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetControlBrush()
{
    __asm {
        mov eax, 0000118Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetControlColor()
{
    __asm {
        mov eax, 0000118Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetCPD()
{
    __asm {
        mov eax, 0000118Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetCursorFrameInfo()
{
    __asm {
        mov eax, 0000118Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetCursorInfo()
{
    __asm {
        mov eax, 0000118Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetDC()
{
    __asm {
        mov eax, 00001190h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetDCEx()
{
    __asm {
        mov eax, 00001191h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetDoubleClickTime()
{
    __asm {
        mov eax, 00001192h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetForegroundWindow()
{
    __asm {
        mov eax, 00001193h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetGuiResources()
{
    __asm {
        mov eax, 00001194h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetGUIThreadInfo()
{
    __asm {
        mov eax, 00001195h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetIconInfo()
{
    __asm {
        mov eax, 00001196h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetIconSize()
{
    __asm {
        mov eax, 00001197h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetImeHotKey()
{
    __asm {
        mov eax, 00001198h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetImeInfoEx()
{
    __asm {
        mov eax, 00001199h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetInternalWindowPos()
{
    __asm {
        mov eax, 0000119Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetKeyboardLayoutList()
{
    __asm {
        mov eax, 0000119Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetKeyboardLayoutName()
{
    __asm {
        mov eax, 0000119Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetKeyboardState()
{
    __asm {
        mov eax, 0000119Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetKeyNameText()
{
    __asm {
        mov eax, 0000119Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetKeyState()
{
    __asm {
        mov eax, 0000119Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetListBoxInfo()
{
    __asm {
        mov eax, 000011A0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetMenuBarInfo()
{
    __asm {
        mov eax, 000011A1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetMenuIndex()
{
    __asm {
        mov eax, 000011A2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetMenuItemRect()
{
    __asm {
        mov eax, 000011A3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetMessage()
{
    __asm {
        mov eax, 000011A4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetMouseMovePointsEx()
{
    __asm {
        mov eax, 000011A5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetObjectInformation()
{
    __asm {
        mov eax, 000011A6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetOpenClipboardWindow()
{
    __asm {
        mov eax, 000011A7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetPriorityClipboardFormat()
{
    __asm {
        mov eax, 000011A8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetProcessWindowStation()
{
    __asm {
        mov eax, 000011A9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetRawInputBuffer()
{
    __asm {
        mov eax, 000011AAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetRawInputData()
{
    __asm {
        mov eax, 000011ABh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetRawInputDeviceInfo()
{
    __asm {
        mov eax, 000011ACh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetRawInputDeviceList()
{
    __asm {
        mov eax, 000011ADh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetRegisteredRawInputDevices()
{
    __asm {
        mov eax, 000011AEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetScrollBarInfo()
{
    __asm {
        mov eax, 000011AFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetSystemMenu()
{
    __asm {
        mov eax, 000011B0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetThreadDesktop()
{
    __asm {
        mov eax, 000011B1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetThreadState()
{
    __asm {
        mov eax, 000011B2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetTitleBarInfo()
{
    __asm {
        mov eax, 000011B3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetUpdateRect()
{
    __asm {
        mov eax, 000011B4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetUpdateRgn()
{
    __asm {
        mov eax, 000011B5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserGetWindowDC()
{
    __asm {
        mov eax, 000011B6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetWindowPlacement()
{
    __asm {
        mov eax, 000011B7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetWOWClass()
{
    __asm {
        mov eax, 000011B8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserHardErrorControl()
{
    __asm {
        mov eax, 000011B9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserHideCaret()
{
    __asm {
        mov eax, 000011BAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserHiliteMenuItem()
{
    __asm {
        mov eax, 000011BBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserImpersonateDdeClientWindow()
{
    __asm {
        mov eax, 000011BCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserInitialize()
{
    __asm {
        mov eax, 000011BDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserInitializeClientPfnArrays()
{
    __asm {
        mov eax, 000011BEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserInitTask()
{
    __asm {
        mov eax, 000011BFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000030h
    }
}

__declspec(naked) ULONG NTAPI NtUserInternalGetWindowText()
{
    __asm {
        mov eax, 000011C0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserInvalidateRect()
{
    __asm {
        mov eax, 000011C1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserInvalidateRgn()
{
    __asm {
        mov eax, 000011C2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserIsClipboardFormatAvailable()
{
    __asm {
        mov eax, 000011C3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserKillTimer()
{
    __asm {
        mov eax, 000011C4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserLoadKeyboardLayoutEx()
{
    __asm {
        mov eax, 000011C5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserLockWindowStation()
{
    __asm {
        mov eax, 000011C6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserLockWindowUpdate()
{
    __asm {
        mov eax, 000011C7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserLockWorkStation()
{
    __asm {
        mov eax, 000011C8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserMapVirtualKeyEx()
{
    __asm {
        mov eax, 000011C9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserMenuItemFromPoint()
{
    __asm {
        mov eax, 000011CAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserMessageCall()
{
    __asm {
        mov eax, 000011CBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserMinMaximize()
{
    __asm {
        mov eax, 000011CCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserMNDragLeave()
{
    __asm {
        mov eax, 000011CDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserMNDragOver()
{
    __asm {
        mov eax, 000011CEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserModifyUserStartupInfoFlags()
{
    __asm {
        mov eax, 000011CFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserMoveWindow()
{
    __asm {
        mov eax, 000011D0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserNotifyIMEStatus()
{
    __asm {
        mov eax, 000011D1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserNotifyProcessCreate()
{
    __asm {
        mov eax, 000011D2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserNotifyWinEvent()
{
    __asm {
        mov eax, 000011D3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserOpenClipboard()
{
    __asm {
        mov eax, 000011D4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserOpenDesktop()
{
    __asm {
        mov eax, 000011D5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserOpenInputDesktop()
{
    __asm {
        mov eax, 000011D6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserOpenWindowStation()
{
    __asm {
        mov eax, 000011D7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserPaintDesktop()
{
    __asm {
        mov eax, 000011D8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserPeekMessage()
{
    __asm {
        mov eax, 000011D9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserPostMessage()
{
    __asm {
        mov eax, 000011DAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserPostThreadMessage()
{
    __asm {
        mov eax, 000011DBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserPrintWindow()
{
    __asm {
        mov eax, 000011DCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserProcessConnect()
{
    __asm {
        mov eax, 000011DDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserQueryInformationThread()
{
    __asm {
        mov eax, 000011DEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserQueryInputContext()
{
    __asm {
        mov eax, 000011DFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserQuerySendMessage()
{
    __asm {
        mov eax, 000011E0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserQueryWindow()
{
    __asm {
        mov eax, 000011E1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserRealChildWindowFromPoint()
{
    __asm {
        mov eax, 000011E2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserRealInternalGetMessage()
{
    __asm {
        mov eax, 000011E3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserRealWaitMessageEx()
{
    __asm {
        mov eax, 000011E4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserRedrawWindow()
{
    __asm {
        mov eax, 000011E5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserRegisterClassExWOW()
{
    __asm {
        mov eax, 000011E6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserRegisterUserApiHook()
{
    __asm {
        mov eax, 000011E7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserRegisterHotKey()
{
    __asm {
        mov eax, 000011E8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserRegisterRawInputDevices()
{
    __asm {
        mov eax, 000011E9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserRegisterTasklist()
{
    __asm {
        mov eax, 000011EAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserRegisterWindowMessage()
{
    __asm {
        mov eax, 000011EBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserRemoveMenu()
{
    __asm {
        mov eax, 000011ECh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserRemoveProp()
{
    __asm {
        mov eax, 000011EDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserResolveDesktop()
{
    __asm {
        mov eax, 000011EEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserResolveDesktopForWOW()
{
    __asm {
        mov eax, 000011EFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSBGetParms()
{
    __asm {
        mov eax, 000011F0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserScrollDC()
{
    __asm {
        mov eax, 000011F1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserScrollWindowEx()
{
    __asm {
        mov eax, 000011F2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtUserSelectPalette()
{
    __asm {
        mov eax, 000011F3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSendInput()
{
    __asm {
        mov eax, 000011F4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetActiveWindow()
{
    __asm {
        mov eax, 000011F5h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetAppImeLevel()
{
    __asm {
        mov eax, 000011F6h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetCapture()
{
    __asm {
        mov eax, 000011F7h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetClassLong()
{
    __asm {
        mov eax, 000011F8h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetClassWord()
{
    __asm {
        mov eax, 000011F9h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetClipboardData()
{
    __asm {
        mov eax, 000011FAh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetClipboardViewer()
{
    __asm {
        mov eax, 000011FBh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetConsoleReserveKeys()
{
    __asm {
        mov eax, 000011FCh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetCursor()
{
    __asm {
        mov eax, 000011FDh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetCursorContents()
{
    __asm {
        mov eax, 000011FEh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetCursorIconData()
{
    __asm {
        mov eax, 000011FFh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetFocus()
{
    __asm {
        mov eax, 00001200h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetImeHotKey()
{
    __asm {
        mov eax, 00001201h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetImeInfoEx()
{
    __asm {
        mov eax, 00001202h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetImeOwnerWindow()
{
    __asm {
        mov eax, 00001203h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetInformationProcess()
{
    __asm {
        mov eax, 00001204h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetInformationThread()
{
    __asm {
        mov eax, 00001205h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetInternalWindowPos()
{
    __asm {
        mov eax, 00001206h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetKeyboardState()
{
    __asm {
        mov eax, 00001207h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetLogonNotifyWindow()
{
    __asm {
        mov eax, 00001208h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetMenu()
{
    __asm {
        mov eax, 00001209h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetMenuContextHelpId()
{
    __asm {
        mov eax, 0000120Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetMenuDefaultItem()
{
    __asm {
        mov eax, 0000120Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetMenuFlagRtoL()
{
    __asm {
        mov eax, 0000120Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetObjectInformation()
{
    __asm {
        mov eax, 0000120Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetParent()
{
    __asm {
        mov eax, 0000120Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetProcessWindowStation()
{
    __asm {
        mov eax, 0000120Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetProp()
{
    __asm {
        mov eax, 00001210h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetScrollInfo()
{
    __asm {
        mov eax, 00001211h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetShellWindowEx()
{
    __asm {
        mov eax, 00001212h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetSysColors()
{
    __asm {
        mov eax, 00001213h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetSystemCursor()
{
    __asm {
        mov eax, 00001214h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetSystemMenu()
{
    __asm {
        mov eax, 00001215h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetSystemTimer()
{
    __asm {
        mov eax, 00001216h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetThreadDesktop()
{
    __asm {
        mov eax, 00001217h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetThreadLayoutHandles()
{
    __asm {
        mov eax, 00001218h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetThreadState()
{
    __asm {
        mov eax, 00001219h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetTimer()
{
    __asm {
        mov eax, 0000121Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowFNID()
{
    __asm {
        mov eax, 0000121Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowLong()
{
    __asm {
        mov eax, 0000121Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowPlacement()
{
    __asm {
        mov eax, 0000121Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowPos()
{
    __asm {
        mov eax, 0000121Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowRgn()
{
    __asm {
        mov eax, 0000121Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowsHookAW()
{
    __asm {
        mov eax, 00001220h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowsHookEx()
{
    __asm {
        mov eax, 00001221h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowStationUser()
{
    __asm {
        mov eax, 00001222h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWindowWord()
{
    __asm {
        mov eax, 00001223h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserSetWinEventHook()
{
    __asm {
        mov eax, 00001224h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtUserShowCaret()
{
    __asm {
        mov eax, 00001225h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserShowScrollBar()
{
    __asm {
        mov eax, 00001226h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserShowWindow()
{
    __asm {
        mov eax, 00001227h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserShowWindowAsync()
{
    __asm {
        mov eax, 00001228h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSoundSentry()
{
    __asm {
        mov eax, 00001229h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserSwitchDesktop()
{
    __asm {
        mov eax, 0000122Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserSystemParametersInfo()
{
    __asm {
        mov eax, 0000122Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserTestForInteractiveUser()
{
    __asm {
        mov eax, 0000122Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserThunkedMenuInfo()
{
    __asm {
        mov eax, 0000122Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserThunkedMenuItemInfo()
{
    __asm {
        mov eax, 0000122Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserToUnicodeEx()
{
    __asm {
        mov eax, 0000122Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserTrackMouseEvent()
{
    __asm {
        mov eax, 00001230h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserTrackPopupMenuEx()
{
    __asm {
        mov eax, 00001231h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserCalcMenuBar()
{
    __asm {
        mov eax, 00001232h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtUserPaintMenuBar()
{
    __asm {
        mov eax, 00001233h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserTranslateAccelerator()
{
    __asm {
        mov eax, 00001234h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserTranslateMessage()
{
    __asm {
        mov eax, 00001235h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserUnhookWindowsHookEx()
{
    __asm {
        mov eax, 00001236h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserUnhookWinEvent()
{
    __asm {
        mov eax, 00001237h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserUnloadKeyboardLayout()
{
    __asm {
        mov eax, 00001238h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserUnlockWindowStation()
{
    __asm {
        mov eax, 00001239h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserUnregisterClass()
{
    __asm {
        mov eax, 0000123Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserUnregisterUserApiHook()
{
    __asm {
        mov eax, 0000123Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserUnregisterHotKey()
{
    __asm {
        mov eax, 0000123Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserUpdateInputContext()
{
    __asm {
        mov eax, 0000123Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserUpdateInstance()
{
    __asm {
        mov eax, 0000123Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserUpdateLayeredWindow()
{
    __asm {
        mov eax, 0000123Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000028h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetLayeredWindowAttributes()
{
    __asm {
        mov eax, 00001240h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetLayeredWindowAttributes()
{
    __asm {
        mov eax, 00001241h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserUpdatePerUserSystemParameters()
{
    __asm {
        mov eax, 00001242h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserUserHandleGrantAccess()
{
    __asm {
        mov eax, 00001243h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserValidateHandleSecure()
{
    __asm {
        mov eax, 00001244h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserValidateRect()
{
    __asm {
        mov eax, 00001245h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserValidateTimerCallback()
{
    __asm {
        mov eax, 00001246h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserVkKeyScanEx()
{
    __asm {
        mov eax, 00001247h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserWaitForInputIdle()
{
    __asm {
        mov eax, 00001248h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserWaitForMsgAndEvent()
{
    __asm {
        mov eax, 00001249h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtUserWaitMessage()
{
    __asm {
        mov eax, 0000124Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserWin32PoolAllocationStats()
{
    __asm {
        mov eax, 0000124Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtUserWindowFromPoint()
{
    __asm {
        mov eax, 0000124Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserYieldTask()
{
    __asm {
        mov eax, 0000124Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserRemoteConnect()
{
    __asm {
        mov eax, 0000124Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserRemoteRedrawRectangle()
{
    __asm {
        mov eax, 0000124Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserRemoteRedrawScreen()
{
    __asm {
        mov eax, 00001250h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserRemoteStopScreenUpdates()
{
    __asm {
        mov eax, 00001251h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtUserCtxDisplayIOCtl()
{
    __asm {
        mov eax, 00001252h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngAssociateSurface()
{
    __asm {
        mov eax, 00001253h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCreateBitmap()
{
    __asm {
        mov eax, 00001254h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCreateDeviceSurface()
{
    __asm {
        mov eax, 00001255h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCreateDeviceBitmap()
{
    __asm {
        mov eax, 00001256h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCreatePalette()
{
    __asm {
        mov eax, 00001257h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngComputeGlyphSet()
{
    __asm {
        mov eax, 00001258h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCopyBits()
{
    __asm {
        mov eax, 00001259h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngDeletePalette()
{
    __asm {
        mov eax, 0000125Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngDeleteSurface()
{
    __asm {
        mov eax, 0000125Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngEraseSurface()
{
    __asm {
        mov eax, 0000125Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngUnlockSurface()
{
    __asm {
        mov eax, 0000125Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngLockSurface()
{
    __asm {
        mov eax, 0000125Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngBitBlt()
{
    __asm {
        mov eax, 0000125Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngStretchBlt()
{
    __asm {
        mov eax, 00001260h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngPlgBlt()
{
    __asm {
        mov eax, 00001261h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000002Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngMarkBandingSurface()
{
    __asm {
        mov eax, 00001262h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngStrokePath()
{
    __asm {
        mov eax, 00001263h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngFillPath()
{
    __asm {
        mov eax, 00001264h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngStrokeAndFillPath()
{
    __asm {
        mov eax, 00001265h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000028h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngPaint()
{
    __asm {
        mov eax, 00001266h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngLineTo()
{
    __asm {
        mov eax, 00001267h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000024h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngAlphaBlend()
{
    __asm {
        mov eax, 00001268h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000001Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngGradientFill()
{
    __asm {
        mov eax, 00001269h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000028h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngTransparentBlt()
{
    __asm {
        mov eax, 0000126Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000020h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngTextOut()
{
    __asm {
        mov eax, 0000126Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000028h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngStretchBltROP()
{
    __asm {
        mov eax, 0000126Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000034h
    }
}

__declspec(naked) ULONG NTAPI NtGdiXLATEOBJ_cGetPalette()
{
    __asm {
        mov eax, 0000126Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiXLATEOBJ_iXlate()
{
    __asm {
        mov eax, 0000126Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiXLATEOBJ_hGetColorTransform()
{
    __asm {
        mov eax, 0000126Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCLIPOBJ_bEnum()
{
    __asm {
        mov eax, 00001270h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiCLIPOBJ_cEnumStart()
{
    __asm {
        mov eax, 00001271h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiCLIPOBJ_ppoGetPath()
{
    __asm {
        mov eax, 00001272h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngDeletePath()
{
    __asm {
        mov eax, 00001273h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCreateClip()
{
    __asm {
        mov eax, 00001274h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000000h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngDeleteClip()
{
    __asm {
        mov eax, 00001275h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBRUSHOBJ_ulGetBrushColor()
{
    __asm {
        mov eax, 00001276h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBRUSHOBJ_pvAllocRbrush()
{
    __asm {
        mov eax, 00001277h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBRUSHOBJ_pvGetRbrush()
{
    __asm {
        mov eax, 00001278h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBRUSHOBJ_hGetColorTransform()
{
    __asm {
        mov eax, 00001279h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiXFORMOBJ_bApplyXform()
{
    __asm {
        mov eax, 0000127Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiXFORMOBJ_iGetXform()
{
    __asm {
        mov eax, 0000127Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_vGetInfo()
{
    __asm {
        mov eax, 0000127Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_pxoGetXform()
{
    __asm {
        mov eax, 0000127Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_cGetGlyphs()
{
    __asm {
        mov eax, 0000127Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000014h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_pifi()
{
    __asm {
        mov eax, 0000127Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_pfdg()
{
    __asm {
        mov eax, 00001280h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_pQueryGlyphAttrs()
{
    __asm {
        mov eax, 00001281h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_pvTrueTypeFontFile()
{
    __asm {
        mov eax, 00001282h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiFONTOBJ_cGetAllGlyphHandles()
{
    __asm {
        mov eax, 00001283h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSTROBJ_bEnum()
{
    __asm {
        mov eax, 00001284h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSTROBJ_bEnumPositionsOnly()
{
    __asm {
        mov eax, 00001285h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiSTROBJ_bGetAdvanceWidths()
{
    __asm {
        mov eax, 00001286h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSTROBJ_vEnumStart()
{
    __asm {
        mov eax, 00001287h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSTROBJ_dwGetCodePage()
{
    __asm {
        mov eax, 00001288h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPATHOBJ_vGetBounds()
{
    __asm {
        mov eax, 00001289h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPATHOBJ_bEnum()
{
    __asm {
        mov eax, 0000128Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPATHOBJ_vEnumStart()
{
    __asm {
        mov eax, 0000128Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPATHOBJ_vEnumStartClipLines()
{
    __asm {
        mov eax, 0000128Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiPATHOBJ_bEnumClipLines()
{
    __asm {
        mov eax, 0000128Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetDhpdev()
{
    __asm {
        mov eax, 0000128Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiEngCheckAbort()
{
    __asm {
        mov eax, 0000128Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiHT_Get8BPPFormatPalette()
{
    __asm {
        mov eax, 00001290h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiHT_Get8BPPMaskPalette()
{
    __asm {
        mov eax, 00001291h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000018h
    }
}

__declspec(naked) ULONG NTAPI NtGdiUpdateTransform()
{
    __asm {
        mov eax, 00001292h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetPUMPDOBJ()
{
    __asm {
        mov eax, 00001293h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiBRUSHOBJ_DeleteRbrush()
{
    __asm {
        mov eax, 00001294h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtGdiUMPDEngFreeUserMem()
{
    __asm {
        mov eax, 00001295h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDrawStream()
{
    __asm {
        mov eax, 00001296h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiMakeObjectXferable()
{
    __asm {
        mov eax, 00001297h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtDxEngGetRedirectionBitmap()
{
    __asm {
        mov eax, 00001298h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetViewportOrgEx()
{
    __asm {
        mov eax, 00001299h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiSetWindowOrgEx()
{
    __asm {
        mov eax, 0000129Ah
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiGetFontFamilyInfo()
{
    __asm {
        mov eax, 0000129Bh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiOffsetViewportOrgEx()
{
    __asm {
        mov eax, 0000129Ch
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtGdiOffsetWindowOrgEx()
{
    __asm {
        mov eax, 0000129Dh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000010h
    }
}

__declspec(naked) ULONG NTAPI NtUserGetMonitorInfo()
{
    __asm {
        mov eax, 0000129Eh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserMonitorFromPoint()
{
    __asm {
        mov eax, 0000129Fh
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtUserMonitorFromRect()
{
    __asm {
        mov eax, 000012A0h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserMonitorFromWindow()
{
    __asm {
        mov eax, 000012A1h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000008h
    }
}

__declspec(naked) ULONG NTAPI NtUserSetScrollBarInfo()
{
    __asm {
        mov eax, 000012A2h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 0000000Ch
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDDICreateDCFromMemory()
{
    __asm {
        mov eax, 000012A3h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

__declspec(naked) ULONG NTAPI NtGdiDdDDIDestroyDCFromMemory()
{
    __asm {
        mov eax, 000012A4h
        mov edx, KUSER_SHARED_SYSCALL
        call dword ptr [edx]
        retn 00000004h
    }
}

