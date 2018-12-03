/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2017 - 2018
*
*  TITLE:       MAIN.C
*
*  VERSION:     1.00.1
*
*  DATE:        19 Nov 2018
*
*  ApiSetSchema Viewer.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

//
// Strict UNICODE
//
#if !defined UNICODE
#error ANSI build is not supported
#endif

//
// Ignored warnings
//
#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable: 6102) // Using %s from failed function call at line %u
#if (_MSC_VER >= 1900)
#pragma warning(disable: 4091) // 'typedef ': ignored on left of '' when no variable is declared
#pragma warning(disable: 4311) // 'type cast': pointer truncation from %s to %s
#pragma warning(disable: 4312) // 'type cast': conversion from %s to %s of greater size
#endif

#if defined (_MSC_VER)
#if (_MSC_VER >= 1910)
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libucrt.lib")
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif
#endif


#define OEMRESOURCE

#include <Windows.h>
#include <commctrl.h>
#include <ntstatus.h>
#include "ntos.h"
#include "apisetx.h"
#include "minirtl\minirtl.h"
#include "treelist.h"
#include "resource.h"

#pragma comment(lib, "ComCtl32.Lib")

typedef struct _TL_SUBITEMS_FIXED {
    ULONG       ColorFlags;
    COLORREF    BgColor;
    COLORREF    FontColor;
    PVOID       UserParam;
    ULONG       Count;
    LPWSTR      Text[2];
} TL_SUBITEMS_FIXED, *PTL_SUBITEMS_FIXED;

HTREEITEM TreeListAddItem(
    _In_ HWND TreeList,
    _In_opt_ HTREEITEM hParent,
    _In_ UINT mask,
    _In_ UINT state,
    _In_ UINT stateMask,
    _In_opt_ LPWSTR pszText,
    _In_opt_ PVOID subitems
);

typedef struct _GUI_CONTEXT {
    HINSTANCE hInstance;
    HANDLE Heap;
    //HWND MainWindow;
    ATOM ListAtom;
    HWND ListWnd;
    BOOL bShutdown;
} GUI_CONTEXT, *PGUI_CONTEXT;

GUI_CONTEXT g_ctx;

HTREEITEM OutNamespaceEntryEx(
    HTREEITEM RootItem,
    PBYTE Namespace,
    ULONG NameOffset,
    ULONG NameLength,
    ULONG Flags,
    BOOL FlagsValid
)
{
    TL_SUBITEMS_FIXED  subitems;
    PWSTR Name, NameCopy, sptr;
    HTREEITEM hSubItem;
    WCHAR szBuffer[20];

    if (NameOffset == 0)
        return 0;

    Name = (PWSTR)RtlOffsetToPointer(Namespace, NameOffset);

    NameCopy = HeapAlloc(g_ctx.Heap, HEAP_ZERO_MEMORY, NameLength + sizeof(WCHAR));
    if (NameCopy == NULL)
        return 0;

    sptr = NameCopy;

    RtlCopyMemory(
        sptr,
        Name,
        NameLength);

    sptr += (NameLength / sizeof(WCHAR));
    *sptr = 0;

    RtlSecureZeroMemory(&subitems, sizeof(subitems));

    subitems.Text[0] = L"";

    if (FlagsValid && Flags) {
        szBuffer[0] = 0;
        ultostr(Flags, szBuffer);
        sptr = szBuffer;
    }
    else {
        sptr = L"";
    }
    subitems.Text[1] = sptr;

    subitems.Count = 2;

    hSubItem = TreeListAddItem(
        g_ctx.ListWnd,
        RootItem,
        TVIF_TEXT | TVIF_STATE,
        (UINT)0,
        (UINT)0,
        NameCopy,
        &subitems);

    HeapFree(g_ctx.Heap, 0, NameCopy);
    return hSubItem;
}

void OutNamespaceValueEx(
    HTREEITEM RootItem,
    PBYTE Namespace,
    ULONG ValueOffset,
    ULONG ValueLength,
    ULONG NameOffset,
    ULONG NameLength,
    ULONG Flags,
    BOOL FlagsValid
)
{
    TL_SUBITEMS_FIXED  subitems;
    PWSTR NamePtr, ValueName = NULL, AliasName = NULL, sptr = NULL;
    WCHAR szBuffer[20];

    RtlSecureZeroMemory(&subitems, sizeof(subitems));

    // print value name

    if (ValueLength) {

        NamePtr = (PWSTR)RtlOffsetToPointer(Namespace, ValueOffset);

        ValueName = HeapAlloc(g_ctx.Heap, HEAP_ZERO_MEMORY, ValueLength + sizeof(WCHAR));
        if (ValueName) {
            sptr = ValueName;

            RtlCopyMemory(
                sptr,
                NamePtr,
                ValueLength);

            sptr += (ValueLength / sizeof(WCHAR));
            *sptr = 0;

        }
    }

    // print value alias
    if (NameLength) {

        NamePtr = (PWSTR)RtlOffsetToPointer(Namespace, NameOffset);

        AliasName = HeapAlloc(g_ctx.Heap, HEAP_ZERO_MEMORY, NameLength + sizeof(WCHAR));
        if (AliasName) {
            sptr = AliasName;

            RtlCopyMemory(
                sptr,
                NamePtr,
                NameLength);

            sptr += (NameLength / sizeof(WCHAR));
            *sptr = 0;

            sptr = AliasName;

            //TreeList_Expand(g_ctx.ListWnd, RootItem, TVE_EXPAND);

        }
    }
    else {
        sptr = L"";
    }
    subitems.Text[0] = sptr;

    if (FlagsValid && Flags) {
        szBuffer[0] = 0;
        ultostr(Flags, szBuffer);
        sptr = szBuffer;
    }
    else {
        sptr = L"";
    }
    subitems.Text[1] = sptr;
    subitems.Count = 2;

    TreeListAddItem(
        g_ctx.ListWnd,
        RootItem,
        TVIF_TEXT | TVIF_STATE,
        (UINT)0,
        (UINT)0,
        ValueName,
        &subitems);

    if (ValueName) HeapFree(g_ctx.Heap, 0, ValueName);
    if (AliasName) HeapFree(g_ctx.Heap, 0, AliasName);
}

/*
* CenterWindow
*
* Purpose:
*
* Centers given window relative to desktop window.
*
*/
VOID CenterWindow(
    _In_ HWND hwnd
)
{
    RECT rc, rcDlg, rcOwner;
    HWND hwndParent = GetDesktopWindow();

    //center window
    if (hwndParent) {
        GetWindowRect(hwndParent, &rcOwner);
        GetWindowRect(hwnd, &rcDlg);
        CopyRect(&rc, &rcOwner);
        OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
        OffsetRect(&rc, -rc.left, -rc.top);
        OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);
        SetWindowPos(hwnd,
            HWND_TOP,
            rcOwner.left + (rc.right / 2),
            rcOwner.top + (rc.bottom / 2),
            0, 0,
            SWP_NOSIZE);
    }
}

/*
* InitTreeList
*
* Purpose:
*
* Intialize TreeList control.
*
*/
BOOL InitTreeList(
    _In_ HWND hwndParent,
    _Out_ ATOM *pTreeListAtom,
    _Out_ HWND *pTreeListHwnd
)
{
    ATOM     TreeListAtom;
    HWND     TreeList;
    HDITEM   hdritem;
    RECT     rc;

    if ((pTreeListAtom == NULL) || (pTreeListHwnd == NULL)) {
        return FALSE;
    }

    GetClientRect(hwndParent, &rc);
    TreeListAtom = InitializeTreeListControl();
    TreeList = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TREELIST, NULL,
        WS_VISIBLE | WS_CHILD | WS_TABSTOP | TLSTYLE_COLAUTOEXPAND, 10, 10,
        rc.right - 20, rc.bottom - 100, hwndParent, NULL, NULL, NULL);

    if (TreeList == NULL) {
        UnregisterClass(MAKEINTATOM(TreeListAtom), g_ctx.hInstance);
        *pTreeListHwnd = NULL;
        *pTreeListAtom = 0;
        return FALSE;
    }

    *pTreeListHwnd = TreeList;
    *pTreeListAtom = TreeListAtom;

    RtlSecureZeroMemory(&hdritem, sizeof(hdritem));
    hdritem.mask = HDI_FORMAT | HDI_TEXT | HDI_WIDTH;
    hdritem.fmt = HDF_LEFT | HDF_BITMAP_ON_RIGHT | HDF_STRING;
    hdritem.cxy = 300;
    hdritem.pszText = TEXT("Namespace");
    TreeList_InsertHeaderItem(TreeList, 0, &hdritem);
    hdritem.cxy = 130;
    hdritem.pszText = TEXT("Alias");
    TreeList_InsertHeaderItem(TreeList, 1, &hdritem);
    hdritem.cxy = 200;
    hdritem.pszText = TEXT("Flags");
    TreeList_InsertHeaderItem(TreeList, 2, &hdritem);

    return TRUE;
}

/*
* TreeListAddItem
*
* Purpose:
*
* Insert new treelist item.
*
*/
HTREEITEM TreeListAddItem(
    _In_ HWND TreeList,
    _In_opt_ HTREEITEM hParent,
    _In_ UINT mask,
    _In_ UINT state,
    _In_ UINT stateMask,
    _In_opt_ LPWSTR pszText,
    _In_opt_ PVOID subitems
)
{
    TVINSERTSTRUCT  tvitem;
    PTL_SUBITEMS    si = (PTL_SUBITEMS)subitems;

    RtlSecureZeroMemory(&tvitem, sizeof(tvitem));
    tvitem.hParent = hParent;
    tvitem.item.mask = mask;
    tvitem.item.state = state;
    tvitem.item.stateMask = stateMask;
    tvitem.item.pszText = pszText;
    tvitem.hInsertAfter = TVI_LAST;
    return TreeList_InsertTreeItem(TreeList, &tvitem, si);
}

void ListApiSetV2(
    _In_ PVOID ApiSetMap,
    _In_ HTREEITEM RootItem
)
{
    API_SET_NAMESPACE_ARRAY_V2 *Namespace = (API_SET_NAMESPACE_ARRAY_V2*)ApiSetMap;

    ULONG i, j;

    API_SET_NAMESPACE_ENTRY_V2 *NsEntry;
    API_SET_VALUE_ARRAY_V2 *ValuesArray;
    API_SET_VALUE_ENTRY_V2 *ValueEntry;

    HTREEITEM hSubItem;

    for (i = 0; i < Namespace->Count; i++) {

        NsEntry = &Namespace->Array[i];

        hSubItem = OutNamespaceEntryEx(
            RootItem,
            (PBYTE)Namespace,
            NsEntry->NameOffset,
            NsEntry->NameLength,
            0,
            FALSE);

        ValuesArray = (API_SET_VALUE_ARRAY_V2*)RtlOffsetToPointer(Namespace, NsEntry->DataOffset);

        for (j = 0; j < ValuesArray->Count; j++) {

            ValueEntry = &ValuesArray->Array[j];

            if (!EMPTY_NAMESPACE_VALUE(
                ValueEntry->ValueOffset,
                ValueEntry->ValueLength,
                ValueEntry->NameOffset,
                ValueEntry->NameLength))
            {
                OutNamespaceValueEx(
                    hSubItem,
                    (PBYTE)Namespace,
                    ValueEntry->ValueOffset,
                    ValueEntry->ValueLength,
                    ValueEntry->NameOffset,
                    ValueEntry->NameLength,
                    0,
                    FALSE);
            }
        }
    }
}

void ListApiSetV4(
    _In_ PVOID ApiSetMap,
    _In_ HTREEITEM RootItem
)
{
    API_SET_NAMESPACE_ARRAY_V4 *Namespace = (API_SET_NAMESPACE_ARRAY_V4*)ApiSetMap;

    ULONG i, j;

    API_SET_NAMESPACE_ENTRY_V4 *NsEntry;
    API_SET_VALUE_ARRAY_V4 *ValuesArray;
    API_SET_VALUE_ENTRY_V4 *ValueEntry;

    HTREEITEM hSubItem;

    for (i = 0; i < Namespace->Count; i++) {

        NsEntry = &Namespace->Array[i];

        hSubItem = OutNamespaceEntryEx(
            RootItem,
            (PBYTE)Namespace,
            NsEntry->NameOffset,
            NsEntry->NameLength,
            NsEntry->Flags,
            TRUE);

        ValuesArray = (API_SET_VALUE_ARRAY_V4*)RtlOffsetToPointer(Namespace, NsEntry->DataOffset);

        for (j = 0; j < ValuesArray->Count; j++) {

            ValueEntry = &ValuesArray->Array[j];

            if (!EMPTY_NAMESPACE_VALUE(
                ValueEntry->ValueOffset,
                ValueEntry->ValueLength,
                ValueEntry->NameOffset,
                ValueEntry->NameLength))
            {
                OutNamespaceValueEx(
                    hSubItem,
                    (PBYTE)Namespace,
                    ValueEntry->ValueOffset,
                    ValueEntry->ValueLength,
                    ValueEntry->NameOffset,
                    ValueEntry->NameLength,
                    ValueEntry->Flags,
                    TRUE);
            }
        }
    }
}

void ListApiSetV6(
    _In_ PVOID ApiSetMap,
    _In_ HTREEITEM RootItem
)
{
    API_SET_NAMESPACE_ARRAY_V6 *Namespace = (API_SET_NAMESPACE_ARRAY_V6*)ApiSetMap;

    ULONG i, j;

    API_SET_NAMESPACE_ENTRY_V6 *NsEntry;
    API_SET_VALUE_ENTRY_V6 *ValueEntry;

    HTREEITEM hSubItem;

    NsEntry = (API_SET_NAMESPACE_ENTRY_V6*)RtlOffsetToPointer(Namespace, Namespace->NamespaceEntryOffset);

    for (i = 0; i < Namespace->Count; i++) {

        hSubItem = OutNamespaceEntryEx(
            RootItem,
            (PBYTE)Namespace,
            NsEntry->NameOffset,
            NsEntry->NameLength,
            NsEntry->Flags,
            TRUE);

        ValueEntry = (API_SET_VALUE_ENTRY_V6*)RtlOffsetToPointer(Namespace, NsEntry->DataOffset);

        for (j = 0; j < NsEntry->Count; j++) {

            if (!EMPTY_NAMESPACE_VALUE(
                ValueEntry->ValueOffset,
                ValueEntry->ValueLength,
                ValueEntry->NameOffset,
                ValueEntry->NameLength))
            {
                OutNamespaceValueEx(
                    hSubItem,
                    (PBYTE)Namespace,
                    ValueEntry->ValueOffset,
                    ValueEntry->ValueLength,
                    ValueEntry->NameOffset,
                    ValueEntry->NameLength,
                    ValueEntry->Flags,
                    TRUE);
            }
            ValueEntry = (API_SET_VALUE_ENTRY_V6*)RtlOffsetToPointer(ValueEntry, sizeof(API_SET_VALUE_ENTRY_V6));
        }
        NsEntry = (API_SET_NAMESPACE_ENTRY_V6*)RtlOffsetToPointer(NsEntry, sizeof(API_SET_NAMESPACE_ENTRY_V6));
    }
}

VOID ListApiSetFromFile()
{
    UINT i;
    HMODULE MappedImageBase;
    PBYTE BaseAddress;
    PIMAGE_NT_HEADERS NtHeaders;
    IMAGE_SECTION_HEADER *SectionTableEntry;
    ULONG DataSize = 0;
    PBYTE DataPtr = NULL;
    ULONG SchemaVersion;
    WCHAR *s;

    HTREEITEM h_tviRootItem;

    MappedImageBase = LoadLibraryEx(L"apisetschema.dll", NULL, LOAD_LIBRARY_AS_DATAFILE);
    if (MappedImageBase == NULL)
        return;

    BaseAddress = (PBYTE)(((ULONG_PTR)MappedImageBase) & ~3);

    NtHeaders = RtlImageNtHeader(BaseAddress);

    SectionTableEntry = (PIMAGE_SECTION_HEADER)((PCHAR)NtHeaders +
        sizeof(ULONG) +
        sizeof(IMAGE_FILE_HEADER) +
        NtHeaders->FileHeader.SizeOfOptionalHeader);

    i = NtHeaders->FileHeader.NumberOfSections;
    while (i > 0) {
        if (*(PULONG)SectionTableEntry->Name == 'ipa.')
            if ((SectionTableEntry->Name[4] == 's') &&
                (SectionTableEntry->Name[5] == 'e') &&
                (SectionTableEntry->Name[6] == 't') &&
                (SectionTableEntry->Name[7] == 0))
            {
                DataSize = SectionTableEntry->SizeOfRawData;
                DataPtr = (PBYTE)BaseAddress + SectionTableEntry->PointerToRawData;
                break;
            }
        i -= 1;
        SectionTableEntry += 1;
    }

    if ((DataPtr == NULL) || (DataSize == 0))
        return;

    SchemaVersion = *(ULONG*)DataPtr;

    h_tviRootItem = TreeListAddItem(
        g_ctx.ListWnd,
        (HTREEITEM)NULL,
        TVIF_TEXT | TVIF_STATE,
        TVIS_EXPANDED,
        TVIS_EXPANDED,
        TEXT("ApiSetSchema"),
        (PVOID)NULL);

    if (h_tviRootItem == 0)
        return;

    switch (SchemaVersion) {
    case API_SET_SCHEMA_VERSION_V2:

        ListApiSetV2(
            DataPtr,
            h_tviRootItem);

        break;

    case API_SET_SCHEMA_VERSION_V4:

        ListApiSetV4(
            DataPtr,
            h_tviRootItem);

        break;

    case API_SET_SCHEMA_VERSION_V6:

        ListApiSetV6(
            DataPtr,
            h_tviRootItem);

        break;

    default:
        s = (WCHAR*)_alloca(200);
        if (s) {
            _strcpy(s, L"unknown schema version=");
            ultostr(SchemaVersion, _strend(s));
            MessageBox(GetDesktopWindow(), s, NULL, MB_OK);
        }
        break;
    }
}

HTREEITEM TreeView_FindLabel(
    _In_ HWND hwnd,
    _In_ HTREEITEM hItemParent,
    _In_ LPCWSTR pszLabel)
{
    TVITEMEX tvi;
    HTREEITEM hChildSearch;
    WCHAR wchLabel[MAX_PATH];

    for (tvi.hItem = TreeView_GetChild(hwnd, hItemParent);
        tvi.hItem;
        tvi.hItem = TreeView_GetNextSibling(hwnd, tvi.hItem))
    {
        tvi.mask = TVIF_TEXT | TVIF_CHILDREN;
        tvi.pszText = wchLabel;
        tvi.cchTextMax = MAX_PATH;
        if (TreeList_GetTreeItem(hwnd, &tvi, NULL)) {
            if (_strcmpi(tvi.pszText, pszLabel) == 0)
                return tvi.hItem;

            if (tvi.cChildren) {
                hChildSearch = TreeView_FindLabel(hwnd, tvi.hItem, pszLabel);
                if (hChildSearch)
                    return hChildSearch;
            }
        }
    }
    return 0;
}

VOID HandleSearchSchema(
    _In_ HWND hwndDlg)
{
    HTREEITEM hItem;
    WCHAR szSchemaName[MAX_PATH * 2];

    RtlSecureZeroMemory(szSchemaName, sizeof(szSchemaName));

    SendDlgItemMessage(
        hwndDlg,
        IDC_SEARCH_EDIT,
        WM_GETTEXT,
        (WPARAM)MAX_PATH,
        (LPARAM)&szSchemaName);

    hItem = TreeView_FindLabel(
        g_ctx.ListWnd,
        TreeView_GetRoot(g_ctx.ListWnd),
        szSchemaName);

    if (hItem) {
        TreeList_EnsureVisible(g_ctx.ListWnd, hItem);
        TreeList_Expand(g_ctx.ListWnd, hItem, TVE_EXPAND);
        SetFocus(g_ctx.ListWnd);
    }
}

VOID HandleWMNotify(
    _In_ HWND   hwndDlg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    TL_SUBITEMS_FIXED *subitems;
    LPNMHDR hdr = (LPNMHDR)lParam;

    HWND TreeList = (HWND)GetWindowLongPtr(g_ctx.ListWnd, TL_TREECONTROL_SLOT);

    TVITEMEX tvi;
    WCHAR szBuffer[MAX_PATH + 1];

    if (hdr->hwndFrom == TreeList) {
        switch (hdr->code) {
        case TVN_ITEMEXPANDED:
        case TVN_SELCHANGED:
            RtlSecureZeroMemory(&tvi, sizeof(tvi));
            RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));

            tvi.mask = TVIF_TEXT;
            tvi.pszText = szBuffer;
            tvi.hItem = TreeList_GetSelection(g_ctx.ListWnd);
            tvi.cchTextMax = MAX_PATH;
            if (TreeList_GetTreeItem(g_ctx.ListWnd, &tvi, &subitems)) {
                SendDlgItemMessage(
                    hwndDlg,
                    IDC_ENTRY_EDIT,
                    WM_SETTEXT,
                    (WPARAM)0,
                    (LPARAM)&szBuffer);
            }

            break;
        default:
            break;
        }
    }
}

INT_PTR CALLBACK AsWindowDialogProc(
    _In_ HWND   hwndDlg,
    _In_ UINT   uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    HANDLE hImage;
    HTREEITEM hRoot;

    switch (uMsg) {

    case WM_INITDIALOG:

        hImage = LoadImage(
            g_ctx.hInstance,
            MAKEINTRESOURCE(IDI_ICON_MAIN),
            IMAGE_ICON,
            0,
            0,
            LR_SHARED);

        if (hImage) {
            SetClassLongPtr(hwndDlg, GCLP_HICON, (LONG_PTR)hImage);
            DestroyIcon(hImage);
        }

        if (InitTreeList(
            hwndDlg,
            &g_ctx.ListAtom,
            &g_ctx.ListWnd))
        {
            ListApiSetFromFile();
        }
        break;

    case WM_SHOWWINDOW:
        if (wParam) {
            CenterWindow(hwndDlg);
            SendDlgItemMessage(hwndDlg, IDC_SEARCH_EDIT, EM_LIMITTEXT, MAX_PATH, 0);
            hRoot = TreeList_GetRoot(g_ctx.ListWnd);
            TreeList_EnsureVisible(g_ctx.ListWnd, hRoot);
            SetFocus(g_ctx.ListWnd);
        }
        break;

    case WM_NOTIFY:
        HandleWMNotify(
            hwndDlg,
            wParam,
            lParam);
        break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {
        case IDC_SEARCH_BUTTON:
            HandleSearchSchema(hwndDlg);
            break;

        case IDOK:
        case IDCANCEL:
            return EndDialog(hwndDlg, S_OK);
            break;
        default:
            break;
        }

    default:
        break;
    }
    return 0;
}

void main()
{
    INITCOMMONCONTROLSEX icex;

    RtlSecureZeroMemory(&g_ctx, sizeof(g_ctx));

    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    g_ctx.hInstance = GetModuleHandle(NULL);
    g_ctx.Heap = HeapCreate(0, 0, 0);

    DialogBoxParam(
        g_ctx.hInstance,
        MAKEINTRESOURCE(IDD_ASDIALOG),
        NULL,
        AsWindowDialogProc,
        0);

    ExitProcess(0);
}
