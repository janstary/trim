CFLAGS	= -Wall -pedantic

PREFIX	= ${DESTDIR}/${HOME}
BINDIR	= ${PREFIX}/bin/
MANDIR	= ${PREFIX}/man/man1/

BIN 	= trim
MAN 	= trim.1

all: ${BIN}

trim: trim.c
	${CC} ${CFLAGS} -o trim trim.c

lint: ${MAN}
	mandoc -Tlint ${MAN}

test: trim
	sh ./example

install: ${BIN} ${MAN}
	install -m 755 -d ${BINDIR}
	install -m 755 -d ${MANDIR}
	install -m 755 ${BIN} ${BINDIR}
	install -m 664 ${MAN} ${MANDIR}

uninstall:
	rm -f ${BINDIR}/${BIN}
	rm -f ${MANDIR}/${MAN}

clean:
	rm -f -- ${BIN} *.{s,u}{8,16,32}{le,be} *.core *~
