SUBDIRS = TTigress TS3 TSiLi TRf
ALLDIRS = $(SUBDIRS) 
#LASTDIR = $(notdir $(CURDIR))

inclibs=  libTigress.so

inclibs+= libS3.so
inclibs+= libSiLi.so
inclibs+= libRfFitter.so


export CFLAGS += -fPIC

.PHONY: subdirs $(ALLDIRS) clean 
subdirs: $(SUBDIRS)

$(ALLDIRS):
	@$(MAKE) -C $@
	$(COMPILESHARED)$@ $(CFLAGS) -olibTAnalysis.so $(OBJECTS)
	cp libTAnalysis.so ..	

clean:
	@$(RM) *a *so *~
	@for dir in $(ALLDIRS); do \
	$(MAKE) -C $$dir $@; \
	done
