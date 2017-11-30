#=============================================================================
# run_encrypt.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the rsa ecrypt system.

# Project name
set hls_prj rsa_encrypt.prj

# Open/reset the project
open_project ${hls_prj} -reset

# Top function of the design is "dut"
set_top dut

# Add design and testbench files
add_files rsa.cpp
add_files -tb test_rsa_encrypt.cpp

open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10

### You can insert your own directives here ###
############################################

# Simulate the C++ design
csim_design -O
# Synthesize the design
csynth_design
# Co-simulate the design
#cosim_design
exit
