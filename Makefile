CMAKE_BUILD_TYPE ?= Debug
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
CMAKE_EXTRA_FLAGS ?=

SRC_DIR := .
BUILD_DIR := build

GEN_CMD := cmake -S${SRC_DIR} -B${BUILD_DIR} -GNinja ${CMAKE_FLAGS} ${CMAKE_EXTRA_FLAGS}
BUILD_TARGET_CMD := cmake --build ${BUILD_DIR} --target

all: wordler

build/.ran-cmake:
	mkdir -p build
	${GEN_CMD}
	touch $@

wordler: build/.ran-cmake
	${BUILD_TARGET_CMD} install

test: wordler
	${BUILD_TARGET_CMD} test

bench: wordler
	${BUILD_DIR}/src/wordler_benchmarks --benchmark_out=${BUILD_DIR}/benchmark_results.json

clean: | build/.ran-cmake
	${BUILD_TARGET_CMD} clean

distclean:
	rm -rf build
	rm -rf bin
