#! /bin/sh

LIBTOOLIZE=libtoolize
AUTOMAKE=automake
ACLOCAL=aclocal
AUTOCONF=autoconf
AUTOHEADER=autoheader

# Check for binaries

[ "x$(which ${LIBTOOLIZE})x" = "xx" ] && {
    echo "${LIBTOOLIZE} not found. Please install it."
    exit 1
}

[ "x$(which ${AUTOMAKE})x" = "xx" ] && {
    echo "${AUTOMAKE} not found. Please install it."
    exit 1
}

[ "x$(which ${ACLOCAL})x" = "xx" ] && {
    echo "${ACLOCAL} not found. Please install it."
    exit 1
}

[ "x$(which ${AUTOCONF})x" = "xx" ] && {
    echo "${AUTOCONF} not found. Please install it."
    exit 1
}

"${ACLOCAL}" \
&& "${LIBTOOLIZE}" --force \
&& "${AUTOHEADER}" \
&& "${AUTOCONF}" \
&& "${AUTOMAKE}" --add-missing
