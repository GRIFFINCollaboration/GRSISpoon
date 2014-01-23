SUBDIRS = TigInput  MidasInterface EventLoop TigFormat TigOscilloscope CalManager RootIOManager  TServer TAnalysis TParser
ALLDIRS = $(SUBDIRS) 
#LASTDIR = $(notdir $(CURDIR))

export CFLAGS += -fPIC

.PHONY: subdirs $(ALLDIRS) clean 
subdirs: $(SUBDIRS)

$(ALLDIRS):
	@$(MAKE) -C $@

clean:
	@$(RM) *a *so *~
	@for dir in $(ALLDIRS); do \
	$(MAKE) -C $$dir $@; \
	done
