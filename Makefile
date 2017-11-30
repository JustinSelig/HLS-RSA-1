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

csim: rsa.cpp test_rsa_encrypt.cpp
	@echo "Compiling & simulating rsa with test_rsa_encrypt on amdpool ..."
	g++ ${CFLAGS} $^ -o rsa -lrt
	./rsa

sw: rsa.cpp rsa_sw.cpp
	@echo "Running pure software test"
	g++ ${CFLAGS} $^ -o rsa-sw -lrt
	./rsa-sw

bitstream: 
	@echo "Synthesizing rsa and creating bitstream on amdpool ..."
	vivado_hls -f run.tcl
	./run_bitstream.sh

vivado:
	@echo "Run Vivado csim and HLS"
	vivado_hls -f run.tcl

encrypt: test_rsa_encrypt.cpp
	@echo "Run Vivado encrypt and HLS"
	vivado_hls -f run_encrypt.tcl

decrypt: test_rsa_decrypt.cpp
	@echo "Run Vivado decrypt and HLS"
	vivado_hls -f run_decrypt.tcl

crt: test_rsa_crt.cpp
	@echo "Run Vivado crt and HLS"
	vivado_hls -f run_crt.tcl

clean:
	rm -rf rsa *.dat *.prj *.log
	rm -rf zedboard_project* xillydemo.bit
