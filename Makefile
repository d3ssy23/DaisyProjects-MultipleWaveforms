# Project Name
TARGET = MultipleWaveforms

# Sources
CPP_SOURCES = MultipleWaveforms.cpp

# Library Locations
LIBDAISY_DIR =  ../../DaisyExamples/libDaisy
DAISYSP_DIR = ../../DaisyExamples/DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
