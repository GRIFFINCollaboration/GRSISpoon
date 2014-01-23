
ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include

CFLAGS += $(shell root-config --cflags)

.PHONY: all clean gone

OBJECTS= TCloverData.o TCloverDataDict.o TCrystalData.o TCrystalDataDict.o TigressHit.o TigressHitDict.o TTigress.o TTigressDict.o TS3.o TS3Data.o S3Hit.o TSiLi.o TSiLiData.o SiLiHit.o TRfFitter.o TRfFitterDict.o

all: libTAnalysis.so #libTAnalysis.a

libTAnalysis.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -olibTAnalysis.so $(OBJECTS)
	cp libTAnalysis.so ..

libTAnalysis.a: $(OBJECTS)
	ar rcs libTAnalysis.a $(OBJECTS)
	cp libTAnalysis.a ..

TCloverData.o: TCloverData.cxx
	g++ -c -fPIC TCloverData.cxx $(INC) `root-config --cflags`

TCloverDataDict.o: TCloverDataDict.cxx
	g++ -c -fPIC TCloverDataDict.cxx $(INC) `root-config --cflags`

TCloverDataDict.cxx: $(BASE)/include/TCloverData.h
	rootcint TCloverDataDict.cxx -c $(BASE)/include/TCloverData.h

TCrystalData.o: TCrystalData.cxx
	g++ -c -fPIC TCrystalData.cxx $(INC) `root-config --cflags`

TCrystalDataDict.o: TCrystalDataDict.cxx
	g++ -c -fPIC TCrystalDataDict.cxx $(INC) `root-config --cflags`

TCrystalDataDict.cxx: $(BASE)/include/TCrystalData.h
	rootcint TCrystalDataDict.cxx -c $(BASE)/include/TCrystalData.h

TTigress.o: TTigress.cxx
	g++ -c -fPIC TTigress.cxx $(INC) `root-config --cflags`

TTigressDict.o: TTigressDict.cxx
	g++ -c -fPIC TTigressDict.cxx $(INC) `root-config --cflags`

TTigressDict.cxx: $(BASE)/include/TTigress.h
	rootcint TTigressDict.cxx -c $(BASE)/include/TTigress.h

TigressHit.o: TigressHit.cxx
	g++ -c -fPIC TigressHit.cxx $(INC) `root-config --cflags`

TigressHitDict.o: TigressHitDict.cxx
	g++ -c -fPIC TigressHitDict.cxx $(INC) `root-config --cflags`

TigressHitDict.cxx: $(BASE)/include/TigressHit.h
	rootcint TigressHitDict.cxx -c $(BASE)/include/TigressHit.h


TS3.o: TS3.cxx
	g++ -c -fPIC TS3.cxx $(INC) `root-config --cflags`

TS3Dict.o: TS3Dict.cxx
	g++ -c -fPIC TS3Dict.cxx $(INC) `root-config --cflags`

TS3Dict.cxx: $(BASE)/include/TS3.h
	rootcint TS3Dict.cxx -c $(BASE)/include/TS3.h

TS3Data.o: TS3Data.cxx
	g++ -c -fPIC TS3Data.cxx $(INC) `root-config --cflags`

TS3DataDict.o: TS3DataDict.cxx
	g++ -c -fPIC TS3DataDict.cxx $(INC) `root-config --cflags`

TS3DataDict.cxx: $(BASE)/include/TS3Data.h
	rootcint TS3DataDict.cxx -c $(BASE)/include/TS3Data.h

S3Hit.o: S3Hit.cxx
	g++ -c -fPIC S3Hit.cxx $(INC) `root-config --cflags`

S3Dict.o: S3HitDict.cxx
	g++ -c -fPIC S3HitDict.cxx $(INC) `root-config --cflags`

S3HitDict.cxx: $(BASE)/include/S3Hit.h
	rootcint S3HitDict.cxx -c $(BASE)/include/S3Hit.h



TSiLi.o: TSiLi.cxx
	g++ -c -fPIC TSiLi.cxx $(INC) `root-config --cflags`

TSiLiDict.o: TSiLiDict.cxx
	g++ -c -fPIC TSiLiDict.cxx $(INC) `root-config --cflags`

TSiLiDict.cxx: $(BASE)/include/TSiLi.h
	rootcint TSiLiDict.cxx -c $(BASE)/include/TSiLi.h

TSiLiData.o: TSiLiData.cxx
	g++ -c -fPIC TSiLiData.cxx $(INC) `root-config --cflags`

TSiLiDataDict.o: TSiLiDataDict.cxx
	g++ -c -fPIC TSiLiDataDict.cxx $(INC) `root-config --cflags`

TSiLiDataDict.cxx: $(BASE)/include/TSiLiData.h
	rootcint TSiLiDataDict.cxx -c $(BASE)/include/TSiLiData.h

SiLiHit.o: SiLiHit.cxx
	g++ -c -fPIC SiLiHit.cxx $(INC) `root-config --cflags`

SiLiDict.o: SiLiHitDict.cxx
	g++ -c -fPIC SiLiHitDict.cxx $(INC) `root-config --cflags`

SiLiHitDict.cxx: $(BASE)/include/SiLiHit.h
	rootcint SiLiHitDict.cxx -c $(BASE)/include/SiLiHit.h

%.o: %.cxx
	$(CXX) -c $^ $(CFLAGS) $(CPPFLAGS)

%Dict.cxx: $(BASE)/include/%.h
	rootcint $@ -c $^

clean:
	$(RM) *.o *~ *Dict.* *a *so

gone:
	$(RM) *Dict.* *a *.o *~

