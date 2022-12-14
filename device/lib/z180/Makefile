# libc/z80 Makefile


srcdir = .
top_builddir = ../../..

AR_S            = ar -S

LIB_TYPE        = RANLIB

TOPDIR = ../../..

SCC = $(TOPDIR)/bin/sdcc -mz180
SAS = $(TOPDIR)/bin/sdasz80

# override PORTDIR defined by super (parent) makefile
override PORTDIR = ../build/z180

include $(srcdir)/../incl.mk

Z80_FLOAT = $(COMMON_FLOAT)

Z80_INT = $(COMMON_INT)

Z80_LONG = $(COMMON_LONG) \
  _divulong.c \
  _mullong.c

Z80_SDCC = $(COMMON_SDCC) \
  _itoa.c \
  _ltoa.c \
  _startup.c \
  sprintf.c \
  vprintf.c

Z80SOURCES = $(addprefix ../,$(Z80_FLOAT) $(Z80_INT) $(Z80_LONG) $(Z80_SDCC))
Z8OBJECTS = $(patsubst %.c,%.rel,$(Z80_FLOAT) $(Z80_INT) $(Z80_LONG) $(Z80_SDCC))

OBJ = divunsigned.rel divsigned.rel divmixed.rel modunsigned.rel modsigned.rel modmixed.rel mul.rel mulchar.rel \
      putchar.rel shift.rel stubs.rel crt0_rle.rel heap.rel fstubs.rel memmove.rel strlen.rel abs.rel crtcall.rel \
      setjmp.rel

LIB = z180.lib
CC = $(SCC)
AS = $(SAS)
ASFLAGS = -plosgff

CFLAGS = -I$(srcdir)/../../include -I. --std-c99

all: $(PORTDIR)/$(LIB) $(PORTDIR)/crt0.rel

$(PORTDIR)/crt0.rel: crt0.rel
	cp crt0.rel $(PORTDIR)/crt0.rel

$(PORTDIR)/$(LIB): $(OBJ) $(Z8OBJECTS) Makefile
ifeq ($(LIB_TYPE), SDCCLIB)
	rm -f $@; \
	../../../bin/sdcclib -a $@ $(OBJ) $(Z8OBJECTS)
else
  ifeq ($(LIB_TYPE), AR)
	$(AR_S) -cq $@ $(OBJ) $(Z8OBJECTS)
  else
    ifeq ($(LIB_TYPE), RANLIB)
	$(AR_S) -cq $@ $(OBJ) $(Z8OBJECTS)
	$(top_builddir)/bin/sdranlib $@
    else
	rm -f $@; \
	for i in $(basename $(OBJ) $(Z8OBJECTS)); do echo $$i >>$@; done
	cp $(OBJ) $(Z8OBJECTS) $(PORTDIR)
    endif
  endif
endif

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

%.rel: %.s
	@# TODO: sdas should place it\'s output in the current dir
	test $(srcdir) = . || cp $< .
	-$(AS) $(ASFLAGS) $(notdir $<)
	test $(srcdir) = . || rm $(notdir $<)

%.rel: ../%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.rel *.sym *.lst *~ $(CLEANSPEC) *.dump* *.asm *.lib

distclean: clean
	rm -f Makefile
