


ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include

CFLAGS += $(shell root-config --cflags)

.PHONY: all clean gone

OBJECTS= TS3.o TS3Data.o TS3DataDict.o  S3Hit.o S3HitDict.o TS3Dict.o

all: libS3.so

libS3.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibS3.so $(OBJECTS)
	cp libS3.so ../..

%.o: %.cxx
	$(CXX) -c $^ $(CFLAGS) $(CPPFLAGS)

%Dict.cxx: $(BASE)/include/%.h
	rootcint $@ -c $^



clean:
	$(RM) *.o *~ *Dict.* *a *so

gone:
	$(RM) *Dict.* *a *.o *~
