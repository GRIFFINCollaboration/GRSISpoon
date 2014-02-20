SUBDIRS = TigInput  MidasInterface EventLoop TigFormat TigOscilloscope CalManager RootIOManager  TServer TAnalysis TParser
ALLDIRS = $(SUBDIRS) 
#LASTDIR = $(notdir $(CURDIR))

export CFLAGS += -fPIC

.PHONY: subdirs $(ALLDIRS) clean 
subdirs: $(SUBDIRS)

$(ALLDIRS):
	@$(MAKE) -C $@
TAnalysis/%: TAnalysis

clean:
	@$(RM) *a *so *~
	@for dir in $(ALLDIRS); do \
	$(MAKE) -C $$dir $@; \
	done

libFormat.so: TigFormat
libOscilloscope.so: TigOscilloscope
libRfFitter.so: TAnalysis/TRf
libS3.so: TAnalysis/TS3
libSharc.so: TAnalysis/TSharc
libSiLi.so: TAnalysis/TSiLi
libTigress.so: TAnalysis/TTigress

lib%.so:
	@cp $</$@ $@




