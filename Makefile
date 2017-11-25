#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and synthesizes the digitrec program
#
# @desc: 1. "make" runs csim by default
#        2. "make csim" compiles & executes the fixed-point implementation
#        3. "make clean" cleans up the directory


# Extract Vivado HLS include path
VHLS_PATH := $(dir $(shell which vivado_hls))/..
VHLS_INC ?= ${VHLS_PATH}/include

CFLAGS = -g -I${VHLS_INC} -ansi

all: csim

csim: rsa.cpp test_rsa.cpp
	@echo "Compiling & simulating rsa on amdpool ..."
	g++ ${CFLAGS} $^ -o rsa -lrt
	./rsa

bitstream: 
	@echo "Synthesizing rsa and creating bitstream on amdpool ..."
	vivado_hls -f run.tcl
	./run_bitstream.sh

vivado:
	@echo "Run Vivado csim and HLS"
	vivado_hls -f run.tcl

clean:
	rm -rf rsa *.dat *.prj *.log
	rm -rf zedboard_project* xillydemo.bit
