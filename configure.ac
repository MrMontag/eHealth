#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([eHealth data collector], [0.0.13], [MrMontag@gmail.com], [eHdc])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-bzip2 subdir-objects])

AC_PROG_CXX

CXXFLAGS="$CXXFLAGS -fpermissive -lpthread -lrt"

# Checks for programs.

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([pthread.h])
AC_CHECK_HEADERS([bcm2835.h], [], [AC_MSG_ERROR([Unable to find bcm2835.h. Please install the bcm2835 library.])])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
