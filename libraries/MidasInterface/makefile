# Makefile

ifndef BASE
BASE=../..
endif

CXXFLAGS = -g -fPIC -O2 -Wall -Wuninitialized

# optional ZLIB library

CXXFLAGS += -DHAVE_ZLIB

CXXFLAGS += -I$(BASE)/include

# ROOT libraries

#ifdef ROOTSYS
#ROOTLIBS  = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs)  -lXMLParser -lThread
#ROOTGLIBS = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs) -lXMLParser -lThread
#RPATH    += -Wl,-rpath,$(ROOTSYS)/lib
CXXFLAGS += -DHAVE_ROOT $(shell $(ROOTSYS)/bin/root-config --cflags) -std=c++0x
#endif

ALL:= libMidasInterface.a libMidasInterface.so

OBJS:=
OBJS += TMidasEvent.o
OBJS += TMidasEventDict.o
OBJS += TMidasFile.o
OBJS += TMidasFileDict.o

ifdef MIDASSYS
CXXFLAGS += -I$(MIDASSYS)/include
OBJS += TMidasOnline.o
endif

#ifdef ROOTSYS
OBJS += XmlOdb.o HttpOdb.o
#endif

all: $(ALL)

libMidasInterface.a: $(OBJS)
	-rm -f $@
	ar -rv $@ $^
	cp -p $@ $(BASE)/libraries

libMidasInterface.so: $(OBJS)
	g++ --shared -Wl,-soname=libMidasInterface.so -olibMidasInterface.so $(OBJS) -L$(ROOTSYS)/lib 
	cp -p $@ $(BASE)/libraries

#%Dict.cxx: %.h
#	LD_LIBRARY_PATH=$(ROOTSYS)/lib $(ROOTSYS)/bin/rootcint -f $@ -c $^

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<

TMidasFileDict.cxx: $(BASE)/include/TMidasFile.h
	rootcint TMidasFileDict.cxx -c $(BASE)/include/TMidasFile.h

TMidasEventDict.cxx: $(BASE)/include/TMidasEvent.h
	rootcint TMidasEventDict.cxx -c $(BASE)/include/TMidasEvent.h


dox:
	doxygen

clean::
	-rm -f *.o *.a *.exe *.so *Dict* $(ALL)

# end
