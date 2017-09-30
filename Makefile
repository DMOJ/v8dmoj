CXX=cl /nologo
CXXFLAGS=/W3 /Ox /Iv8inc /EHsc
LDFLAGS=v8lib/v8_base_0.lib \
        v8lib/v8_base_1.lib \
        v8lib/v8_libbase.lib \
        v8lib/v8_libplatform.lib \
        v8lib/v8_libsampler.lib \
        v8lib/v8_snapshot.lib \
        v8lib/icuuc.lib \
        v8lib/icui18n.lib \
        advapi32.lib \
        shlwapi.lib \
        winmm.lib \
        dbghelp.lib

all: build v8dmoj

build:
	mkdir build

clean:
	del /q v8dmoj
	del /s /q build

input.cc: v8dmoj.h
output.cc: v8dmoj.h
binio.cc: v8dmoj.h
runtime.cc: v8dmoj.h
v8dmoj.cc: v8dmoj.h

build/input.obj: input.cc
build/output.obj: output.cc
build/binio.obj: binio.cc
build/runtime.obj: runtime.cc
build/v8dmoj.obj: v8dmoj.cc

v8dmoj: build/binio.obj build/input.obj build/output.obj build/runtime.obj build/v8dmoj.obj
	$(CXX) $(LDFLAGS) /Fe$@ $**

.cc{build}.obj::
	$(CXX) $(CXXFLAGS) /Fobuild\ $<
