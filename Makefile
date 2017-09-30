CXX=clang++ -stdlib=libc++
CXXFLAGS=-Wall -O3 -march=native -std=gnu++11 -Iv8inc
LDFLAGS=-static -pthread v8lib/icudtl_dat.o -Wl,--start-group \
            v8lib/libv8_base.a \
            v8lib/libv8_libbase.a \
            v8lib/libv8_libplatform.a \
            v8lib/libv8_libsampler.a \
            v8lib/libv8_snapshot.a \
            v8lib/libicuuc.a \
            v8lib/libicui18n.a \
        -Wl,--end-group -lrt -s -Wl,--gc-sections

all: build v8dmoj

build:
	mkdir build

clean:
	rm -f v8dmoj
	rm -rf build

input.cc: v8dmoj.h
output.cc: v8dmoj.h
runtime.cc: v8dmoj.h
v8dmoj.cc: v8dmoj.h

build/input.o: input.cc
build/output.o: output.cc
build/runtime.o: runtime.cc
build/v8dmoj.o: v8dmoj.cc

v8dmoj: build/input.o build/output.o build/runtime.o build/v8dmoj.o
	$(CXX) $^ $(LDFLAGS) -o $@

build/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
