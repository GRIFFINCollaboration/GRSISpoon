

ifndef BASE
BASE = ../..
endif

INC = -I$(BASE)/include
INC += -I$(MIDASSYS)/include
INCD = $(BASE)/include

#ROOTFUNCTIONS = ../libRootFunctions/libRootFunctions.a
OBJS= TPeriodicClass.o EventLoop.o TPeriodicClassDict.o EventLoopDict.o

all: libEventLoop.a libEventLoop.so

CFLAGS = -std=c++0x

libEventLoop.a: $(OBJS)  
	ar rcs libEventLoop.a TPeriodicClass.o EventLoop.o 
	cp libEventLoop.a ..

libEventLoop.so: $(OBJS)
	g++ --shared $(CLAGS) -Wl,-soname=libEventLoop.so -olibEventLoop.so $(OBJS)
	cp libEventLoop.so ..

#########################################################################
#########################################################################


TPeriodicClass.o: TPeriodicClass.cxx
	g++ -c -fPIC $(CLFAGS) TPeriodicClass.cxx $(INC) `root-config --cflags`

TPeriodicClassDict.o: TPeriodicClassDict.cxx
	g++ -c -fPIC $(CLFAGS) TPeriodicClassDict.cxx $(INC) `root-config --cflags`

TPeriodicClassDict.cxx: $(INCD)/TPeriodicClass.hxx
	rootcint TPeriodicClassDict.cxx -c $(INCD)/TPeriodicClass.hxx

#########################################################################
#########################################################################


EventLoop.o: EventLoop.cxx 
	g++ -c -fPIC $(CFLAGS) EventLoop.cxx $(INC) `root-config --cflags`

EventLoopDict.o: EventLoopDict.cxx
	g++ -c -fPIC $(CFLAGS) EventLoopDict.cxx $(INC) `root-config --cflags`

EventLoopDict.cxx: $(INCD)/EventLoop.h
	rootcint EventLoopDict.cxx -c $(INCD)/EventLoop.h

#########################################################################
#########################################################################


clean:
	$(RM) *.o *~ *.a *.so *Dict*

gone:
	$(RM) *Dict*
	$(RM)	*.a
	$(RM) *.so
	$(RM) *.o
	$(RM) *~

