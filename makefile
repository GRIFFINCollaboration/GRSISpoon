SUBDIRS = src libraries
ALLDIRS = $(SUBDIRS) 

PLATFORM := $(shell uname)

export PLATFORM:= $(PLATFORM)

export CFLAGS = -std=c++0x -O2 -I$(PWD)/include

ifeq ($(PLATFORM),Darwin)
export CFLAGS += -DOS_DARWIN --stdlib=libc++
export LFLAGS = -dynamiclib -single_module -undefined dynamic_lookup
export SHAREDSWITCH = -install_name # ENDING SPACE
export CPP = xcrun clang++
else
export SHAREDSWITCH = -shared -Wl,-soname,#NO ENDING SPACE
# export LFLAGS = -fPIC
export CPP = g++
endif
export COMPILESHARED   = $(CPP) $(LFLAGS) $(SHAREDSWITCH)#NO ENDING SPACE

export BASE:= $(CURDIR)
#export MDASSYS:= /opt/midas-64

.PHONY: all subdirs $(ALLDIRS) clean 
all: print subdirs grsisort

print:
	echo $(PLATFORM)

subdirs: $(SUBDIRS)

src: libraries

$(ALLDIRS):
	@$(MAKE) -C $@

grsisort: src bin
	mv $</$@ bin/$@

bin:
	@mkdir $@

clean:
	@$(RM) *~
	$(RM) ./bin/grsisort
	@for dir in $(ALLDIRS); do \
	$(MAKE) -C $$dir $@; \
	done

