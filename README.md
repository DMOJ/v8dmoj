# v8dmoj
V8-based JavaScript interpreter for online judging

## Building on Linux
You must have `git`, `clang`, and GNU `make` installed.

 1. `git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git`
 2. `export PATH=$PATH:$(pwd)/depot_tools`
 3. `gclient`
 4. `fetch v8`
 5. `cd v8`
 6. Find the Chrome stable v8 version on `https://omahaproxy.appspot.com/`.
 7. `git checkout <the version from step 6>`.
 8. `gclient sync`
 9. `tools/dev/v8gen.py x64.release`
10. Run `gn args out.gn/x64.release` and add:
    ```
    is_component_build = false
    v8_static_library = true
    use_sysroot = false
    treat_warnings_as_errors = false
    icu_use_data_file = false
    v8_use_external_startup_data = false
    ```
11. `ninja -C out.gn/x64.release`
12. `mkdir <path to v8dmoj>/v8lib`
13. `find out.gn/x64.release/obj/ -name '*.a' -exec cp {} <path to v8dmoj>/v8lib \;`
14. `cp out.gn/x64.release/obj/third_party/icu/icudata/icudtl_dat.o ~/v8dmoj/v8lib/`
15. `cp -R include <path to v8dmoj>/v8inc`
16. `cd <path to v8dmoj>`
17. `make`

## Building on Windows
 1. Download [depot tools](https://storage.googleapis.com/chrome-infra/depot_tools.zip) and unpack into a directory called `depot_tools`.
 2. Open a command prompt window and `cd` into the parent directory of `depot_tools`, and run:
    ```
    set PATH=%cd%\depot_tools;%PATH%
    set DEPOT_TOOLS_WIN_TOOLCHAIN=0
    set GYP_MSVS_OVERRIDE_PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0
    set WINDOWSSDKDIR=C:\Program Files (x86)\Windows Kits\10
    ```
    You may need to adapt the version of Visual Studio and the Windows SDK.
 3. `gclient`
 4. `fetch v8`
 5. `cd v8`
 6. Find the Chrome stable v8 version on `https://omahaproxy.appspot.com/`.
 7. `git checkout <the version from step 6>`.
 8. `gclient sync`
 9. `tools/dev/v8gen.py x64.release`
10. Run `gn args out.gn/x64.release` and add:
    ```
    is_component_build = false
    v8_static_library = true
    treat_warnings_as_errors = false
    icu_use_data_file = false
    v8_use_external_startup_data = false
    ```
11. `ninja -C out.gn/x64.release`
12. `mkdir [path to v8dmoj]\v8lib`
13. `for /R out.gn\x64.release\obj %f in (*.lib) do @copy /y %f [path to v8dmoj]\v8lib\ > nul`
14. `xcopy /s /y include C:\Users\Quantum\code\DMOJ\v8dmoj\v8inc\`
15. `cd [path to v8dmoj]`
16. `nmake`
