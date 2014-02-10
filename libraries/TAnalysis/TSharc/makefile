


ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include

CFLAGS += $(shell root-config --cflags)

.PHONY: all clean gone

OBJECTS=  TSharc.o TSharcData.o TSharcDataDict.o TSharcHit.o TSharcHitDict.o TSharcDict.o

all: libSharc.so

libSharc.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibSharc.so $(OBJECTS)
	cp libSharc.so ../..

%.o: %.cxx
	$(CXX) -c $^ $(CFLAGS) $(CPPFLAGS)

%Dict.cxx: $(BASE)/include/%.h
	rootcint $@ -c $^



clean:
	$(RM) *.o *~ *Dict.* *a *so

gone:
	$(RM) *Dict.* *a *.o *~
