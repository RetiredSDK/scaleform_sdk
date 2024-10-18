# Makefile for Scaleform GFx builds

SOURCES=pcre_chartables.c pcre_compile.c pcre_config.c pcre_dfa_exec.c pcre_exec.c \
		pcre_fullinfo.c pcre_get.c pcre_globals.c pcre_info.c pcre_maketables.c \
		pcre_newline.c pcre_ord2utf8.c pcre_refcount.c pcre_study.c pcre_tables.c \
		pcre_try_flipped.c pcre_ucd.c pcre_valid_utf8.c pcre_version.c pcre_xclass.c
OBJECTS=$(SOURCES:.c=.o)

LIB=libpcre.a

all: $(SOURCES) $(LIB)
	
$(LIB): $(OBJECTS)
	$(AR) $(LIB) $(OBJECTS)
	$(RANLIB) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -DHAVE_CONFIG_H -c $<

clean:
	$(RM) -f $(OBJECTS) $(LIB)
