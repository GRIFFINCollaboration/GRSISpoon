ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TFragment.o TTigFragmentDict.o TFragmentDict.o TFragmentQueue.o TFragmentQueueDict.o

all: libTigFormat.a libTigress.so

libTigress.so: $(OBJECTS)
	g++ --shared $(CFLAGS) -Wl,-soname=libTigress.so -olibTigress.so $(OBJECTS)
	cp libTigress.so ..

libTigFormat.a: $(OBJECTS)
	ar rcs libTigFormat.a $(OBJECTS)
	cp libTigFormat.a ..

########################################
########################################

TFragment.o: TFragment.cxx
	g++ -c -fPIC $(CFLAGS) $< $(INC) `root-config --cflags`

TFragmentDict.o: TFragmentDict.cxx
	g++ -c -fPIC $(CFLAGS) $< $(INC) `root-config --cflags`

TFragmentDict.cxx: $(INCD)/TFragment.h
	rootcint $@ -c $<

TTigFragmentDict.o: TTigFragmentDict.cxx
	g++ -c -fPIC $(CFLAGS) TTigFragmentDict.cxx $(INC) `root-config --cflags`

TTigFragmentDict.cxx: $(INCD)/TTigFragment.h
	rootcint TTigFragmentDict.cxx -c $(INCD)/TTigFragment.h

########################################
########################################

TFragmentQueue.o: TFragmentQueue.cxx
	g++ -c -fPIC $(CFLAGS) TFragmentQueue.cxx $(INC) `root-config --cflags`

TFragmentQueueDict.o: TFragmentQueueDict.cxx
	g++ -c -fPIC $(CFLAGS) -DNO_MUTEX TFragmentQueueDict.cxx $(INC) `root-config --cflags`

TFragmentQueueDict.cxx: $(INCD)/TFragmentQueue.h
	rootcint TFragmentQueueDict.cxx -c $(INCD)/TFragmentQueue.h

########################################
########################################


clean:
	$(RM) *.o *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a *.o *~

