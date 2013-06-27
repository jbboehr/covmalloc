
EXTRA_DIST = Readme.md
SUBDIRS = test

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

libcovmalloc_la_LDFLAGS = -ldl -avoid-version -module -shared -export-dynamic


# Alias for test (old habits die hard)
test: check


.PHONY: convenience-link clean-convenience-link

convenience-link: $(lib_LTLIBRARIES)
	@for soname in `echo $(lib_LTLIBRARIES) | sed s/\.la/.so/`; do \
		echo "$$soname: creating convenience link from $(top_builddir)/.libs to $(top_builddir)"; \
		rm -f $(top_builddir)/$$soname ; \
		test -e $(abs_builddir)/.libs/$$soname && \
		cd $(top_builddir) && \
		$(LN_S) $(abs_builddir)/.libs/$$soname $$soname || true;\
	done

clean-convenience-link:
	@for soname in `echo $(lib_LTLIBRARIES) | sed s/\.la/.so/`; do \
		echo "$$soname: cleaning convenience links"; \
		test -e $(top_builddir)/$$soname && rm -f $(top_builddir)/$$soname || true; \
	done

all-local:: convenience-link

clean-local:: clean-convenience-link gcov-clean lcov-clean


# Coverage
if GCOV
coverage-init: 
	lcov --directory . --zerocounters -q

coverage-main:
	lcov --capture --compat-libtool --directory . --output-file covmalloc_test.info
	genhtml -o test_coverage -t "covmalloc test coverage" --num-spaces 4 covmalloc_test.info

coverage: all coverage-init test coverage-main

gcov-clean:
	find . -name '*.gcda' -delete
	find . -name '*.gcno' -delete

lcov-clean:
	rm -rf test_coverage
	rm -f covmalloc_test.info

else
gcov-clean:
lcov-clean:
endif
