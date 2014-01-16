ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include -I$(MIDASSYS)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= RootIOManager.o RootIOManagerDict.o 

all: libRootIOManager.a libRootIOManager.so

libRootIOManager.so: $(OBJECTS)
	g++ --shared $(CFLAGS) -Wl,-soname=libRootIOManager.so -olibRootIOManager.so $(OBJECTS)
	cp libRootIOManager.so ..

libRootIOManager.a: $(OBJECTS)
	ar rcs libRootIOManager.a $(OBJECTS)
	cp libRootIOManager.a ..

########################################
########################################

RootIOManager.o: RootIOManager.cxx
	g++ -c -fPIC $(CFLAGS) RootIOManager.cxx $(INC) `root-config --cflags`

RootIOManagerDict.o: RootIOManagerDict.cxx
	g++ -c -fPIC $(CFLAGS) RootIOManagerDict.cxx $(INC) `root-config --cflags`

RootIOManagerDict.cxx: $(INCD)/RootIOManager.h
	rootcint RootIOManagerDict.cxx -c $(INCD)/RootIOManager.h

########################################
########################################


clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~

