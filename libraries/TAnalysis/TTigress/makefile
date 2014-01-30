


ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include

CFLAGS += $(shell root-config --cflags)

.PHONY: all clean gone

OBJECTS= TCloverData.o TCloverDataDict.o TCrystalData.o TCrystalDataDict.o TigressHit.o TigressHitDict.o TTigress.o TTigressDict.o

all: libTigress.so

libTigress.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibTigress.so $(OBJECTS)
	cp libTigress.so ../..

%.o: %.cxx
	$(CXX) -c $^ $(CFLAGS) $(CPPFLAGS)

%Dict.cxx: $(BASE)/include/%.h
	rootcint $@ -c $^



clean:
	$(RM) *.o *~ *Dict.* *a *so

gone:
	$(RM) *Dict.* *a *.o *~
