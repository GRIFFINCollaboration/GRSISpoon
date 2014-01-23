
ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TTigOFrame.o TTigOscilloscope.o TTigOscilloscopeDict.o 

all: libOscilloscope.so #libOscilloscope.a

libOscilloscope.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibOscilloscope.so $(OBJECTS)
	cp libOscilloscope.so ..

#libOscilloscope.a: $(OBJECTS)
#	ar rcs libOscilloscope.a $(OBJECTS)
#	cp libOscilloscope.a ..

TTigOscilloscope.o: TTigOscilloscope.o
	g++ -c -fPIC $(CFLAGS) TTigOscilloscope.cxx $(INC) `root-config --cflags`

TTigOscilloscopeDict.o: TTigOscilloscopeDict.cxx
	g++ -c -fPIC $(CFLAGS) TTigOscilloscopeDict.cxx $(INC) `root-config --cflags`

TTigOscilloscopeDict.cxx: $(INCD)/TTigOscilloscope.h
	rootcint TTigOscilloscopeDict.cxx -c $(INCD)/TTigOscilloscope.h

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

