SUBDIRS = TigInput  MidasInterface EventLoop TigFormat TigOcilloscope CalManager RootIOManager  TServer TAnalysis TParser
ALLDIRS = $(SUBDIRS) 
#LASTDIR = $(notdir $(CURDIR))

.PHONY: subdirs $(ALLDIRS) clean 
subdirs: $(SUBDIRS)

$(ALLDIRS):
	@$(MAKE) -C $@

clean:
	@$(RM) *a *so *~
	@for dir in $(ALLDIRS); do \
	$(MAKE) -C $$dir $@; \
	done
