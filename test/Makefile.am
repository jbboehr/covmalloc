
check_PROGRAMS = test

test_SOURCES = $(UTILS) test.c

TESTS = test
TESTS_ENVIRONMENT = \
	top_srcdir=$(top_srcdir) \
	top_builddir=$(top_builddir) \
	tokenizer_spec=$(top_srcdir)/spec/handlebars/specs/tokenizer.yml \
	parser_spec=$(top_srcdir)/spec/handlebars/specs/parser.yml \
	handlebars_specdir=$(top_srcdir)/spec/handlebars/specs/ \
	mustache_specdir=$(top_srcdir)/spec/mustache/specs/ \
	tokenizer_spec_outfile=$(top_srcdir)/test/test_tokenizer.c \
	parser_spec_outfile=$(top_srcdir)/test/test_parser.c

TESTS_ENVIRONMENT += LD_PRELOAD=$(top_builddir)/libcovmalloc.so

AM_CPPFLAGS = -I$(top_builddir)/src -I$(top_srcdir)/src -I$(top_srcdir)/test
AM_LDFLAGS = -static
LDADD = $(top_builddir)/libcovmalloc.la
