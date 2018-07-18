# SPDX-License-Identifier: LGPL-2.1-or-later
# Copyright © 2010-2018 ANSSI. All Rights Reserved.
AC_PREREQ(2.59)

m4_define(clipqt_version_major, 2)
m4_define(clipqt_version_minor, 0)
m4_define(clipqt_version_micro, 1)

AC_INIT([libClipQt],
      clipqt_version_major.clipqt_version_minor.clipqt_version_micro,
      [clipos@ssi.gouv.fr])
AC_CONFIG_SRCDIR(config/ClipConfigFile.h)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.10])
AC_PROG_LIBTOOL

dnl ===========================================================================

CLIPCONFIG_VERSION_INFO=clipqt_version_major:clipqt_version_micro:0
AC_SUBST(CLIPCONFIG_VERSION_INFO)
CLIPWIDGETS_VERSION_INFO=clipqt_version_major:clipqt_version_micro:0
AC_SUBST(CLIPWIDGETS_VERSION_INFO)

AC_PROG_CXX
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG
AC_CONFIG_FILES([config/ClipConfig.pc])
AC_CONFIG_FILES([widgets/ClipWidgets.pc])

dnl ===========================================================================
dnl === Local macros
dnl ===========================================================================

dnl Checks for programs.

[
if test "x$GCC" = "xyes"; then
  CFLAGS="$CFLAGS -Wall -Wextra \
	-Wstrict-prototypes -Wmissing-prototypes \
	-Wcast-qual -Wcast-align -Wpointer-arith \
	-Wnested-externs"
fi
]

dnl Checks for header files.
dnl AC_HEADER_STDC
dnl AC_CHECK_HEADERS()


dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_C_CONST

dnl Checks for QT lib
PKG_CHECK_MODULES(QT4_CORE, QtCore,,
    AC_MSG_ERROR([[
***
*** Qt4 Core is required.
***]])
)

PKG_CHECK_MODULES(QT4_GUI, QtGui,,
    AC_MSG_ERROR([[
***
*** Qt4 Gui is required.
***]])
)

AC_OUTPUT(Makefile config/Makefile widgets/Makefile)
