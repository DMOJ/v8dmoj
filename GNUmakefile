CXX=clang++ -stdlib=libc++
CXXFLAGS=-Wall -O3 -std=gnu++11 -Iv8inc
LDFLAGS=-static -pthread -nostdlib++ -Wl,-O2 -Wl,--gc-sections v8lib/icudtl_dat.o -Wl,--start-group \
            v8lib/libc++.a \
            v8lib/libc++abi.a \
            v8lib/libv8_libbase.a \
            v8lib/libv8_libplatform.a \
            v8lib/libv8_base_without_compiler.a \
            v8lib/libicui18n.a \
            v8lib/libicuuc.a \
            v8lib/libtorque_generated_definitions.a \
            v8lib/libv8_libsampler.a \
            v8lib/libinspector.a \
            v8lib/libinspector_string_conversions.a \
            v8lib/libv8_compiler.a \
            v8lib/libv8_snapshot.a \
            v8lib/libchrome_zlib.a \
            v8lib/adler32_simd.o \
        -Wl,--end-group -lrt -s

all: build v8dmoj

build:
	mkdir build

clean:
	rm -f v8dmoj
	rm -rf build

input.cc: v8dmoj.h
output.cc: v8dmoj.h
binio.cc: v8dmoj.h
runtime.cc: v8dmoj.h
v8dmoj.cc: v8dmoj.h

build/input.o: input.cc
build/output.o: output.cc
build/binio.o: binio.cc
build/runtime.o: runtime.cc
build/v8dmoj.o: v8dmoj.cc

v8dmoj: build/binio.o build/input.o build/output.o build/runtime.o build/v8dmoj.o
	$(CXX) $^ $(LDFLAGS) -o $@

build/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
