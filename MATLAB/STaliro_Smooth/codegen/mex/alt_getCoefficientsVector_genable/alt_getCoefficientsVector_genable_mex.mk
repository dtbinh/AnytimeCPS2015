START_DIR = /home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth

MATLAB_ROOT = /usr/local/MATLAB/R2015b
MAKEFILE = alt_getCoefficientsVector_genable_mex.mk

include alt_getCoefficientsVector_genable_mex.mki


SRC_FILES =  \
	alt_getCoefficientsVector_genable_mexutil.c \
	alt_getCoefficientsVector_genable_data.c \
	alt_getCoefficientsVector_genable_initialize.c \
	alt_getCoefficientsVector_genable_terminate.c \
	alt_getCoefficientsVector_genable.c \
	log2.c \
	error.c \
	eml_int_forloop_overflow_check.c \
	mpower.c \
	scalexpAlloc.c \
	permn2.c \
	MeyerWavelet.c \
	prod.c \
	_coder_alt_getCoefficientsVector_genable_info.c \
	_coder_alt_getCoefficientsVector_genable_api.c \
	_coder_alt_getCoefficientsVector_genable_mex.c \
	alt_getCoefficientsVector_genable_emxutil.c

MEX_FILE_NAME_WO_EXT = alt_getCoefficientsVector_genable_mex
MEX_FILE_NAME = $(MEX_FILE_NAME_WO_EXT).mexa64
TARGET = $(MEX_FILE_NAME)

SYS_LIBS = 


#
#====================================================================
# gmake makefile fragment for building MEX functions using Unix
# Copyright 2007-2014 The MathWorks, Inc.
#====================================================================
#
OBJEXT = o
.SUFFIXES: .$(OBJEXT)

OBJLISTC = $(SRC_FILES:.c=.$(OBJEXT))
OBJLISTCPP  = $(OBJLISTC:.cpp=.$(OBJEXT))
OBJLIST  = $(OBJLISTCPP:.cu=.$(OBJEXT))

target: $(TARGET)

ML_INCLUDES = -I "$(MATLAB_ROOT)/simulink/include"
ML_INCLUDES+= -I "$(MATLAB_ROOT)/toolbox/shared/simtargets"
SYS_INCLUDE = $(ML_INCLUDES)

# Additional includes

SYS_INCLUDE += -I "$(START_DIR)"
SYS_INCLUDE += -I "$(START_DIR)/codegen/mex/alt_getCoefficientsVector_genable"
SYS_INCLUDE += -I "./interface"
SYS_INCLUDE += -I "$(MATLAB_ROOT)/extern/include"
SYS_INCLUDE += -I "."

EML_LIBS = -lemlrt -lcovrt -lut -lmwmathutil -lmwblas 
SYS_LIBS += $(CLIBS) $(EML_LIBS)


EXPORTFILE = $(MEX_FILE_NAME_WO_EXT)_mex.map
ifeq ($(Arch),maci)
  EXPORTOPT = -Wl,-exported_symbols_list,$(EXPORTFILE)
  COMP_FLAGS = -c $(CFLAGS) -DMX_COMPAT_32
  CXX_FLAGS = -c $(CXXFLAGS) -DMX_COMPAT_32
  LINK_FLAGS = $(filter-out %mexFunction.map, $(LDFLAGS))
else ifeq ($(Arch),maci64)
  EXPORTOPT = -Wl,-exported_symbols_list,$(EXPORTFILE)
  COMP_FLAGS = -c $(CFLAGS) -DMX_COMPAT_32
  CXX_FLAGS = -c $(CXXFLAGS) -DMX_COMPAT_32
  LINK_FLAGS = $(filter-out %mexFunction.map, $(LDFLAGS))
else
  EXPORTOPT = -Wl,--version-script,$(EXPORTFILE)
  COMP_FLAGS = -c $(CFLAGS) -DMX_COMPAT_32 $(OMPFLAGS)
  CXX_FLAGS = -c $(CXXFLAGS) -DMX_COMPAT_32 $(OMPFLAGS)
  LINK_FLAGS = $(filter-out %mexFunction.map, $(LDFLAGS)) 
endif
LINK_FLAGS += $(OMPLINKFLAGS)
ifeq ($(Arch),maci)
  LINK_FLAGS += -L$(MATLAB_ROOT)/sys/os/maci
endif
ifeq ($(EMC_CONFIG),optim)
  ifeq ($(Arch),mac)
    COMP_FLAGS += $(CDEBUGFLAGS)
    CXX_FLAGS += $(CXXDEBUGFLAGS)
  else
    COMP_FLAGS += $(COPTIMFLAGS)
    CXX_FLAGS += $(CXXOPTIMFLAGS)
  endif
  LINK_FLAGS += $(LDOPTIMFLAGS)
else
  COMP_FLAGS += $(CDEBUGFLAGS)
  CXX_FLAGS += $(CXXDEBUGFLAGS)
  LINK_FLAGS += $(LDDEBUGFLAGS)
endif
LINK_FLAGS += -o $(TARGET)
LINK_FLAGS += 

CCFLAGS =  $(COMP_FLAGS) $(USER_INCLUDE) $(SYS_INCLUDE)
CPPFLAGS =   $(CXX_FLAGS) $(USER_INCLUDE) $(SYS_INCLUDE)

%.$(OBJEXT) : %.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : %.cpp
	$(CXX) $(CPPFLAGS) "$<"

# Additional sources

%.$(OBJEXT) : $(START_DIR)/%.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : $(START_DIR)/codegen/mex/alt_getCoefficientsVector_genable/%.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : interface/%.c
	$(CC) $(CCFLAGS) "$<"



%.$(OBJEXT) : $(START_DIR)/%.cu
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : $(START_DIR)/codegen/mex/alt_getCoefficientsVector_genable/%.cu
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : interface/%.cu
	$(CC) $(CCFLAGS) "$<"



%.$(OBJEXT) : $(START_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) "$<"

%.$(OBJEXT) : $(START_DIR)/codegen/mex/alt_getCoefficientsVector_genable/%.cpp
	$(CXX) $(CPPFLAGS) "$<"

%.$(OBJEXT) : interface/%.cpp
	$(CXX) $(CPPFLAGS) "$<"



$(TARGET): $(OBJLIST) $(MAKEFILE)
	$(LD) $(EXPORTOPT) $(OBJLIST) $(LINK_FLAGS) $(SYS_LIBS)

#====================================================================

