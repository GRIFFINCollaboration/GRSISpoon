
ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TParser.o TParserDict.o 

all: libTParser.a libTParser.so

libTParser.so: $(OBJECTS)
	g++ --shared $(CFLAGS) -Wl,-soname=libTParser.so -olibTParser.so $(OBJECTS)
	cp libTParser.so ..

libTParser.a: $(OBJECTS)
	ar rcs libTParser.a $(OBJECTS)
	cp libTParser.a ..


TParser.o: TParser.cxx
	g++ -c -fPIC $(CFLAGS) TParser.cxx $(INC) `root-config --cflags`

TParserDict.o: TParserDict.cxx
	g++ -c -fPIC $(CFLAGS) TParserDict.cxx $(INC) `root-config --cflags`

TParserDict.cxx: $(INCD)/TParser.h
	rootcint TParserDict.cxx -c $(INCD)/TParser.h



clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~ *so

