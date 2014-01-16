
ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TTigOFrame.o TTigOcilloscope.o TTigOcilloscopeDict.o 

all: libTigOcilloscope.a libTigOcilloscope.so

libTigOcilloscope.so: $(OBJECTS)
	g++ --shared $(CFLAGS) -Wl,-soname=libTigOcilloscope.so -olibTigOcilloscope.so $(OBJECTS)
	cp libTigOcilloscope.so ..

libTigOcilloscope.a: $(OBJECTS)
	ar rcs libTigOcilloscope.a $(OBJECTS)
	cp libTigOcilloscope.a ..

TTigOcilloscope.o: TTigOcilloscope.o
	g++ -c -fPIC $(CFLAGS) TTigOcilloscope.cxx $(INC) `root-config --cflags`

TTigOcilloscopeDict.o: TTigOcilloscopeDict.cxx
	g++ -c -fPIC $(CFLAGS) TTigOcilloscopeDict.cxx $(INC) `root-config --cflags`

TTigOcilloscopeDict.cxx: $(INCD)/TTigOcilloscope.h
	rootcint TTigOcilloscopeDict.cxx -c $(INCD)/TTigOcilloscope.h

TTigOFrame.o: TTigOFrame.cxx
	g++ -c -fPIC $(CFLAGS) TTigOFrame.cxx $(INC) `root-config --cflags`

#TigFrameDict.o: TigFrameDict.cxx
#	g++ -c -fPIC TigInputDict.cxx $(INC) `root-config --cflags`

#TigFrameDict.cxx: $(INCD)/TigFrame.h
#	rootcint TigInputDict.cxx -c $(INCD)/TigInput.h



clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~ *so

