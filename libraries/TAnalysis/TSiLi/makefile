


ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include

CFLAGS += $(shell root-config --cflags)

.PHONY: all clean gone

OBJECTS=  TSiLi.o TSiLiData.o TSiLiDataDict.o SiLiHit.o SiLiHitDict.o TSiLiDict.o

all: libSiLi.so

libSiLi.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibSiLi.so $(OBJECTS)
	cp libSiLi.so ../..

%.o: %.cxx
	$(CXX) -c $^ $(CFLAGS) $(CPPFLAGS)

%Dict.cxx: $(BASE)/include/%.h
	rootcint $@ -c $^



clean:
	$(RM) *.o *~ *Dict.* *a *so

gone:
	$(RM) *Dict.* *a *.o *~
