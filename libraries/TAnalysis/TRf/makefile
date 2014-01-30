


ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include

CFLAGS += $(shell root-config --cflags)

.PHONY: all clean gone

OBJECTS= TRfFitter.o TRfFitterDict.o

all: libRfFitter.so

libRfFitter.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibRfFitter.so $(OBJECTS)
	cp libRfFitter.so ../..

%.o: %.cxx
	$(CXX) -c $^ $(CFLAGS) $(CPPFLAGS)

%Dict.cxx: $(BASE)/include/%.h
	rootcint $@ -c $^



clean:
	$(RM) *.o *~ *Dict.* *a *so

gone:
	$(RM) *Dict.* *a *.o *~
