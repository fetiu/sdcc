# Regression test specification for the pic14 target running with gpsim

CC_FOR_BUILD = $(CC)

# path to gpsim
ifdef GPSIM_PATH
  GPSIM := $(WINE) $(GPSIM_PATH)/gpsim$(EXEEXT)
else
  GPSIM := $(WINE) gpsim$(EXEEXT)
endif

ifndef SDCC_BIN_PATH
  ifndef CROSSCOMPILING
    SDCCFLAGS += --nostdinc -I$(top_srcdir)/device/include/pic14 -I$(top_srcdir)/device/non-free/include/pic -I$(top_srcdir)
    LINKFLAGS += --nostdlib -L$(top_builddir)/device/lib/build/pic14 -L$(top_builddir)/device/non-free/lib/build/pic
  else
    SDCCFLAGS += --non-free
  endif
else
  SDCCFLAGS += --non-free
endif

ifdef CROSSCOMPILING
  SDCCFLAGS += -I$(top_srcdir)
endif

SDCCFLAGS += -mpic14 -pp16f877 --less-pedantic -Wl,-q -DREENTRANT=__reentrant
LINKFLAGS += libsdcc.lib libm.lib

OBJEXT = .o
BINEXT = .cod

EXTRAS = $(PORT_CASES_DIR)/testfwk$(OBJEXT) $(PORT_CASES_DIR)/support$(OBJEXT)

# Rule to link into .ihx
%$(BINEXT): %$(OBJEXT) $(EXTRAS)
	-$(SDCC) $(SDCCFLAGS) $(LINKFLAGS) $(EXTRAS) $< -o $@

%$(OBJEXT): %.c
	-$(SDCC) $(SDCCFLAGS) -c $< -o $@

$(PORT_CASES_DIR)/%$(OBJEXT): $(PORTS_DIR)/$(PORT)/%.c
	-$(SDCC) $(SDCCFLAGS) -c $< -o $@

.PRECIOUS: gen/pic14/testfwk.o gen/pic14/support.o

$(PORT_CASES_DIR)/%$(OBJEXT): fwk/lib/%.c
	$(SDCC) $(SDCCFLAGS) -c $< -o $@

# run simulator with 25 seconds timeout
%.out: %$(BINEXT) $(CASES_DIR)/timeout
	mkdir -p $(dir $@)
	-$(CASES_DIR)/timeout 25 $(GPSIM) -i -s $< -c $(PORTS_DIR)/pic14/gpsim.cmd > $@ || \
	  echo -e --- FAIL: \"timeout, simulation killed\" in $(<:$(BINEXT)=.c)"\n"--- Summary: 1/1/1: timeout >> $@
	python $(srcdir)/get_ticks.py < $@ >> $@
	-grep -n FAIL $@ /dev/null || true

$(CASES_DIR)/timeout: fwk/lib/timeout.c
	$(CC_FOR_BUILD) $(CFLAGS) $< -o $@

_clean:
