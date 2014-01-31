
ifndef BASE
BASE = ../..
endif
INC =  -I$(BASE)/include
INC += -I$(MIDASSYS)/include
INCD = $(BASE)/include

export CFLAGS += `root-config --cflags`

.PHONY: all clean gone

OBJECTS=TigInput.o TigInputDict.o
TARGETS=libTigInput.so
ifeq	($(PLATFORM),Linux)
PERMOBJECTS = words.o
TARGETS += libTigInput.a
endif


all: $(TARGETS)

libTigInput.so: $(OBJECTS) $(PERMOBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -o$@ $^
	cp libTigInput.so ..

libTigInput.a: $(OBJECTS) $(PERMOBJECTS)
	ar rcs libTigInput.a $^
	cp libTigInput.a ..

TigInput.o: TigInput.cxx
	g++ -c $(CFLAGS) TigInput.cxx $(INC)

TigInputDict.o: TigInputDict.cxx
	g++ -c $(CFLAGS) TigInputDict.cxx $(INC)

TigInputDict.cxx: $(INCD)/TigInput.h
	rootcint TigInputDict.cxx -c $(INCD)/TigInput.h



clean:
	$(RM) $(OBJECTS) *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a $(OBJECTS) *~ *so

