ifndef BASE
BASE = ..
endif

INC = -I$(BASE)/include
INC += -I$(MIDASSYS)/include

INCD = $(BASE)/include

LIBDIR = -L$(BASE)/libraries
LIBDIR += -L$(MIDASSYS)/linux/lib


GCC = g++ 
ROOT = `root-config --cflags`
LDROOT = `root-config --glibs`

LIBS = -lTigInput
LIBS += -lMidasInterface
LIBS += -lXMLParser   
LIBS += -lEventLoop
LIBS += -lTigress
LIBS += -lTigOcilloscope
LIBS += -lRootIOManager
LIBS += -lCalManager
LIBS += -lTServer
LIBS += -lTParser
LIBS += -lmidas

LIBS += -lutil
LIBS += -lrt
LIBS += -lz

OBJECTS = main.o TigScope.o TigScopeDict.o 

all:grsisort

grsisort: $(OBJECTS)
	$(GCC) $(INC) $(CFLAGS) $(OBJECTS) $(LIBDIR) $(LIBS) $(LDROOT) -o grsisort

main.o: main.cxx
	$(GCC) -c $(CFLAGS) main.cxx $(INC) $(ROOT)

TigScope.o: TigScope.cxx
	$(GCC) -c $(CFLAGS) TigScope.cxx $(INC) $(ROOT)

TigScopeDict.o: TigScopeDict.cxx
	g++ -c -fPIC $(CFLAGS) TigScopeDict.cxx $(INC) `root-config --cflags`

TigScopeDict.cxx: $(INCD)/TigScope.h
	rootcint TigScopeDict.cxx -c $(INCD)/TigScope.h




clean:
	$(RM) *~ *o *a *Dict*

gone:
	$(RM) *Dict* *~ *o *a grsisort

