
ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TigInput.o TigInputDict.o 

all: libTigInput.a libTigInput.so

libTigInput.so: $(OBJECTS)
	g++ --shared $(CFLAGS) -Wl,-soname=libTigInput.so -olibTigInput.so $(OBJECTS)
	cp libTigInput.so ..

libTigInput.a: $(OBJECTS)
	ar rcs libTigInput.a $(OBJECTS)
	cp libTigInput.a ..


TigInput.o: TigInput.cxx
	g++ -c -fPIC $(CFLAGS) TigInput.cxx $(INC) `root-config --cflags`

TigInputDict.o: TigInputDict.cxx
	g++ -c -fPIC $(CFLAGS) TigInputDict.cxx $(INC) `root-config --cflags`

TigInputDict.cxx: $(INCD)/TigInput.h
	rootcint TigInputDict.cxx -c $(INCD)/TigInput.h



clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~ *so

