OUTPUT = svc_mem

DEBUG	= 1

STACKSIZE 	= 8192

CC		= armcc
AS 		= armasm
LD		= armlink
LIB             = armlib
RM		= rm
MODBIN          = modbin
MAKEBANNER	= MakeBanner

CFLAGS	 = -bigend -za1 -zps0 -zi4 -fa -fh -fx -fpu none -arch 3 -apcs '3/32/fp/swst/wide/softfp'
ASFLAGS	 = -bigend -fpu none -arch 3 -apcs '3/32/fp/swst'
LDFLAGS	 = -aif -reloc -ro-base 0x00 -dupok -remove -nodebug -verbose
INCPATH  = ${TDO_DEVKIT_PATH}/include
LIBPATH  = ${TDO_DEVKIT_PATH}/lib
INCFLAGS = -I$(INCPATH)/3do -I$(INCPATH)/community

LIBS 	= $(LIBPATH)/3do/clib.lib \
	  $(LIBPATH)/community/svc_funcs.lib \
	  $(LIBPATH)/3do/subroutinestartup.o

SRC_S = $(wildcard src/*.s)
SRC_C = $(wildcard src/*.c)

OBJ += $(SRC_S:src/%.s=build/%.s.o)
OBJ += $(SRC_C:src/%.c=build/%.c.o)

all: builddir example_folio.lib example.privfolio

builddir:
	mkdir -p build

clean:
	$(RM) -rfv build/

build/%.s.o: src/%.s
	$(AS) $(INCFLAGS) $(ASFLAGS) $< -o $@

build/%.c.o: src/%.c
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@

build/%.cpp.o: src/%.cpp
	$(CXX) $(INCFLAGS) $(CXXFLAGS) -c $< -o $@

build/example_folio.lib: build/example_folio_lib.c.o
	$(LIB) -c $@ $<

example_folio.lib: builddir build/example_folio.lib

build/example.privfolio.unsigned: build/example_folio.c.o
	$(LD) -o $@ $(LDFLAGS) $(LIBS) $<

example.privfolio.unsigned: builddir build/example.privfolio.unsigned

build/example.privfolio: example.privfolio.unsigned
	$(MODBIN) --stack=$(STACKSIZE) --flags=2 --sign=3do --subsystype=1 --type=4 --name=example build/$< $@

example.privfolio: builddir build/example.privfolio

install: example_folio.lib example.privfolio src/example_folio.h
	cp -fv build/example.privfolio ${TDO_DEVKIT_PATH}/takeme/System/Folios/
	cp -fv build/example_folio.lib ${TDO_DEVKIT_PATH}/lib/community/
	cp -fv src/example_folio.h ${TDO_DEVKIT_PATH}/include/community/

.PHONY: builddir install example_folio.lib example.privfolio
