
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = covmalloc.pc

ACLOCAL_AMFLAGS = -I m4

if GCC
# These flags are gcc specific
export AM_CFLAGS = -Wall -Wextra -Wdeclaration-after-statement  \
    -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
endif

include_HEADERS = covmalloc.h

lib_LTLIBRARIES=libcovmalloc.la

libcovmalloc_la_SOURCES = covmalloc.c covmalloc.h

# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
libcovmalloc_la_LDFLAGS = -ldl -version-info 0:0:0
