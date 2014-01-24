ifndef BASE
BASE = ..
endif

INC = -I$(BASE)/include
INC += -I$(MIDASSYS)/include

INCD = $(BASE)/include

LIBDIR = -L$(BASE)/libraries
ifeq ($(PLATFORM),Darwin)
LIBDIR += -L$(MIDASSYS)/darwin/lib
else ifeq ($(PLATFORM),Linux)
LIBDIR += -L$(MIDASSYS)/linux/lib
endif

ROOT = `root-config --cflags`
LDROOT = `root-config --glibs`

LIBS = -lTigInput
LIBS += -lMidasInterface
LIBS += -lXMLParser   
LIBS += -lEventLoop
LIBS += -lFormat
LIBS += -lOscilloscope
LIBS += -lRootIOManager
LIBS += -lCalManager
LIBS += -lTServer
LIBS += -lTParser
LIBS += -lPyROOT
LIBS += -lmidas

LIBS += -lutil
ifeq ($(PLATFORM),Linux)
LIBS += -lrt
endif
LIBS += -lz

OBJECTS = main.o TigScope.o TigScopeDict.o 

all:grsisort

grsisort: $(OBJECTS)
	$(CPP) $(INC) $(CFLAGS) $(OBJECTS) $(LIBDIR) $(LIBS) $(LDROOT) -o grsisort

main.o: main.cxx
	$(CPP) -c $(CFLAGS) main.cxx $(INC) $(ROOT)

TigScope.o: TigScope.cxx
	$(CPP) -c $(CFLAGS) TigScope.cxx $(INC) $(ROOT)

TigScopeDict.o: TigScopeDict.cxx
	$(CPP) -c -fPIC $(CFLAGS) TigScopeDict.cxx $(INC) `root-config --cflags`

TigScopeDict.cxx: $(INCD)/TigScope.h
	rootcint TigScopeDict.cxx -c $(INCD)/TigScope.h




clean:
	$(RM) *~ *o *a *Dict*

gone:
	$(RM) *Dict* *~ *o *a grsisort

