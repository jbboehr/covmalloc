
AC_PREREQ(2.61)
AC_INIT([covmalloc], [0.0.1-dev], [jbboehr@gmail.com], [covmalloc],
        [https://github.com/jbboehr/covmalloc])

AC_DEFINE([PACKAGE_DESCRIPTION], ["malloc for unit test coverage"], [Description])
AC_SUBST([PACKAGE_DESCRIPTION], ["malloc for unit test coverage"])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# gcov
AC_ARG_ENABLE([gcov], AS_HELP_STRING([--enable-gcov], [Enable gcov]))
if test "x$enable_gcov" == "xyes"; then
    AC_DEFINE([GCOV], [1], [Defined if gcov is enabled])
    LDFLAGS="$LDFLAGS -coverage -lgcov"
    CFLAGS="$CFLAGS -g -O0 -coverage" # -disable-shared ?
fi

AM_CONDITIONAL([GCC], [test x$GCC = xyes])
AM_CONDITIONAL([GCOV], [test x$enable_gcov = xyes])

# Checks for programs
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_LN_S

# Checks for header files
AC_HEADER_STDC
AC_CHECK_HEADERS(stddef.h)

# Checks for functions
AC_CHECK_FUNCS(calloc malloc realloc free)

# Checks for types
AC_TYPE_SIZE_T

# Checks for system
AC_EXEEXT

AC_CONFIG_FILES([
  covmalloc.pc
  Makefile
  test/Makefile
])
AC_OUTPUT
