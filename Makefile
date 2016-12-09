.PHONY: all install dist clean distclean

PACKAGE = ulog
VERSION = 0.0.0
DIST = Makefile ${PACKAGE}.h LICENSE

PREFIX ?= /usr/local
CC ?= gcc

CFLAGS += -Wall -Wextra -pedantic -std=c99

all: example

example: example.c $(PACKAGE).h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

install: ${PACKAGE}.h
	install -D -m644 ${PACKAGE}. ${DESTDIR}${PREFIX}/include/${PACKAGE}.h

dist: ${DIST}
	mkdir -p ${PACKAGE}-${VERSION}
	cp ${DIST} ${PACKAGE}-${VERSION}
	tar -cf ${PACKAGE}-${VERSION}.tar ${PACKAGE}-${VERSION}
	gzip -fk ${PACKAGE}-${VERSION}.tar
	xz -f ${PACKAGE}-${VERSION}.tar

clean:
	rm -f example

distclean:
	rm -rf ${PACKAGE}-${VERSION}{,.tar,.tar.gz,.tar.xz}
