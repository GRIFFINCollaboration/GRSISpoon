ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TServer.o TServerDict.o 

all: libTServer.so #libTServer.a

libTServer.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibTServer.so $(OBJECTS)
	cp libTServer.so ..

libTServer.a: $(OBJECTS)
	ar rcs libTServer.a $(OBJECTS)
	cp libTServer.a ..

########################################
########################################

TServer.o: TServer.cxx
	g++ -c -fPIC $(CFLAGS) TServer.cxx $(INC) `root-config --cflags`

TServerDict.o: TServerDict.cxx
	g++ -c -fPIC $(CFLAGS) TServerDict.cxx $(INC) `root-config --cflags`

TServerDict.cxx: $(INCD)/TServer.h
	rootcint TServerDict.cxx -c $(INCD)/TServer.h

########################################
########################################


clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~

