TARGETS=process

CXXFLAGS += `root-config --cflags`
CXXFLAGS += -I$(GRSISYS)/include -O2

LDFLAGS += -L$(GRSISYS)/libraries
LDLIBS += `root-config --libs` -lFormat -lCalManager -lRootIOManager -lTreePlayer

.PHONY:all clean
all: $(TARGETS)

process: process.o empty_process.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o:%.cxx
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	@$(RM) $(TARGETS) *.o