CXXFLAGS=-Wall -O3 -std=gnu++14 -Imonolith/include
LDFLAGS=-static -pthread -Wl,-O2 -s
LIBS=monolith/libv8_monolith.a -lm -lrt -ldl

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
	$(CXX) $(LDFLAGS) -Wl,--start-group $^ $(LIBS) -Wl,--end-group -o $@

build/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
