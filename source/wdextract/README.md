
# wdextract
## Extract Windows Defender database from vdm files and unpack it

Based on original PowerShell script https://gist.github.com/mattifestation/3af5a472e11b7e135273e71cb5fed866

Rewrote to C++ because it is much faster than any script.

### Usage wdextract "vdm filename" 

+ This program distributed as-is;
+ Uses ZLIB Data Compression Library (https://github.com/madler/zlib);
+ Built with MSVC 2017 with SDK 17763.
