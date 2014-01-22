
ifndef BASE
BASE = ../..
endif
INC = -I$(BASE)/include
INCD = $(BASE)/include

.PHONY: all clean gone

OBJECTS= TigInput.o TigInputDict.o 

all: libTigInput.a libTigInput.so

ifeq	($(PLATFROM),Linux)
libTigInput.so: $(OBJECTS) words.o
	g++ --shared $(CFLAGS) -Wl,-install_name libTigInput.so -olibTigInput.so $^
	cp libTigInput.so ..

libTigInput.a: $(OBJECTS) words.o
	ar rcs libTigInput.a $^
	cp libTigInput.a ..
else
libTigInput.so: $(OBJECTS)
	$(COMPILESHARED)$@ $(CFLAGS) -o $@ $^
	cp libTigInput.so ..

.PHONY: libTigInput.a
libTigInput.a:
	echo 'done'
endif



TigInput.o: TigInput.cxx
	g++ -c -fPIC $(CFLAGS) TigInput.cxx $(INC) `root-config --cflags`

TigInputDict.o: TigInputDict.cxx
	g++ -c -fPIC $(CFLAGS) TigInputDict.cxx $(INC) `root-config --cflags`

TigInputDict.cxx: $(INCD)/TigInput.h
	rootcint TigInputDict.cxx -c $(INCD)/TigInput.h



clean:
	$(RM) $(OBJECTS) *~ *Dict* *a *so

gone:
	$(RM) *Dict* *a $(OBJECTS) *~ *so

