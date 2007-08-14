#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(xtcc, 0.0, NxD_in@yahoo.com)
AC_CONFIG_SRCDIR([const_defs.h])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AM_PROG_LEX

AM_INIT_AUTOMAKE(xtcc,0.0)

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfl':
AC_CHECK_LIB([fl], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_CHECK_MEMBERS([struct stat.st_blksize])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset strdup strtol])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
