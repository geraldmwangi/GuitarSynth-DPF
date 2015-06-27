#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = GuitarSynth

# --------------------------------------------------------------
# Files to build


OBJS_DSP = \
	gsengine.cpp.o \
	synthbase.cpp.o \
	guitarsynthdspplugin.cpp.o \
	gausssynth.cpp.o \
	sinussynth.cpp.o \
	sawsynth.cpp.o \
	squaresynth.cpp.o \
	parameterwithref.cpp.o \
	parameteredobject.cpp.o \
	parameterupdatewave.cpp.o


OBJS_UI = guitarsynthguiplugin.cpp.o\
	    dial.cpp.o

# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif

ifeq ($(LINUX),true)
TARGETS += ladspa
ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_LIBLO),true)
TARGETS += dssi
endif
endif
endif

ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
