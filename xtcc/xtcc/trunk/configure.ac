#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(xtcc, 0.0, NxD_in@yahoo.com)
AC_CONFIG_SRCDIR([const_defs.h])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX

AM_INIT_AUTOMAKE(xtcc, 0.0, NxD_in@yahoo.com)
# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfl':
#AC_CHECK_LIB([fl], [main])
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h float.h libintl.h limits.h malloc.h stddef.h stdlib.h string.h])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset strdup strtol])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
