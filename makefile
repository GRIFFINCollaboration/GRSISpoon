SUBDIRS = src libraries
ALLDIRS = $(SUBDIRS) 

PLATFORM := $(shell uname)

export PLATFROM:= $(PLATFORM)

export CFLAGS = -std=c++0x -O2 #--enable-libstdcxx-time

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

grsisort: src
	cp $^/grsisort bin/$@

clean:
	@$(RM) *~
	@for dir in $(ALLDIRS); do \
	$(MAKE) -C $$dir $@; \
	done

