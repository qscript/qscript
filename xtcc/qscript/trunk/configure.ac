#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(qscript, 0.0, NxD_in@yahoo.com)
AM_INIT_AUTOMAKE	
#AC_CONFIG_SRCDIR([qscript.y])
AC_CONFIG_SRCDIR([const_defs.h])
#AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strdup])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
