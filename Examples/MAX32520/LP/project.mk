# This file can be used to set build configuration
# variables.  These variables are defined in a file called 
# "Makefile" that is located next to this one.

# For instructions on how to use this system, see
# https://analog-devices-msdk.github.io/msdk/USERGUIDE/#build-system

#BOARD=MAX32520FTHR
# ^ For example, you can uncomment this line to make the 
# project build for the "MAX32520FTHR" board.

# **********************************************************

# Add your config here!

# Use local linker file that restricts SRAM usage to
# SRAM0 and SRAM1 to prevent hardfault when all other
# SRAMs shutdown.
override LINKERFILE=lp-sla.ld 