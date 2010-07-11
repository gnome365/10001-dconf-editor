#!/bin/bash

set -e

if [ "$1" = "clean" ]; then
  rm -f aclocal.m4 configure missing install-sh depcomp ltmain.sh \
        config.* `find . -name Makefile.in` compile libtool
  rm -rf autom4te.cache
  exit
fi

if automake-1.11 --version > /dev/null; then
  automake=automake-1.11
else
  automake=automake
fi

gtkdocize --docdir docs --flavour no-tmpl
libtoolize --automake
aclocal ${ACLOCAL_FLAGS}
${automake} --add-missing --foreign
autoconf

CFLAGS=${CFLAGS=-ggdb -Werror}
LDFLAGS=${LDFLAGS=-Wl,-O1}
export CFLAGS LDFLAGS

if test -z "$NOCONFIGURE"; then
  ./configure "$@"
fi

