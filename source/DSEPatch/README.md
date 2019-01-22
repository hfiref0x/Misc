
# DSEPatch
## Windows x64 Driver Signature Enforcement Overrider

# System Requirements

x64 Windows Vista/7/8/8.1/10.

Windows 10: warning, see PatchGuard note below.

DSEPatch designed only for x64 Windows.

Administrative privilege is required.

Obsolete, do not use, see PatchGuard note below.

# Build 

DSEPatch comes with full source code.
In order to build from source you need Microsoft Visual Studio 2013 U4 and later versions.

# How it work

It uses WinNT/Turla VirtualBox kernel mode exploit technique to "patch" ntoskrnl callback structure filled by CI.dll. It is named g_CiCallbacks on Windows 7 and SeCiCallbacks on everything above. DSEPatch replaces CiValidateImageHeader and CiValidateImageData callbacks in this structure with stub routine that always return STATUS_SUCCESS. Original state can be restored - run dsepatch with -r command, e.g. dsepatch -r 

AS-IS, no warranty.

# PatchGuard incompatibility

Windows 10 PatchGuard is aware of this. Bugcheck is 109, 0 - generic data region.

# Authors

(c) 2016 - 2019 DSEPatch Project
