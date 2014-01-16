ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TChannel.o TChannelDict.o CalibrationManager.o CalibrationManagerDict.o

all: libCalManager.a libCalManager.so

libCalManager.so: $(OBJECTS)
	g++ --shared $(CFLAGS) -Wl,-soname=libCalManager.so -olibCalManager.so $(OBJECTS)
	cp libCalManager.so ..

libCalManager.a: $(OBJECTS)
	ar rcs libCalManager.a $(OBJECTS)
	cp libCalManager.a ..

########################################
########################################

TChannel.o: TChannel.cxx
	g++ -c -fPIC $(CFLAGS) TChannel.cxx $(INC) `root-config --cflags`

TChannelDict.o: TChannelDict.cxx
	g++ -c -fPIC $(CFLAGS) TChannelDict.cxx $(INC) `root-config --cflags`

TChannelDict.cxx: $(INCD)/TChannel.h
	rootcint TChannelDict.cxx -c $(INCD)/TChannel.h

########################################
########################################

CalibrationManager.o: CalibrationManager.cxx
	g++ -c -fPIC $(CFLAGS) CalibrationManager.cxx $(INC) `root-config --cflags`

CalibrationManagerDict.o: CalibrationManagerDict.cxx
	g++ -c -fPIC $(CFLAGS) CalibrationManagerDict.cxx $(INC) `root-config --cflags`

CalibrationManagerDict.cxx: $(INCD)/CalibrationManager.h
	rootcint CalibrationManagerDict.cxx -c $(INCD)/CalibrationManager.h

########################################
########################################


clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~

