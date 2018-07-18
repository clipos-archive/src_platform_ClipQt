# SPDX-License-Identifier: LGPL-2.1-or-later
# Copyright © 2010-2018 ANSSI. All Rights Reserved.

lib_LTLIBRARIES = libClipConfig.la

libClipConfigincludedir = $(includedir)/clip/ClipConfig
libClipConfiginclude_HEADERS = \
			CCException.h \
			ClipConfigFile.h \
			ClipProfile.h \
			ConfigFile.h \
			SimpleConfigFile.h

libClipConfig_la_SOURCES = \
			$(libClipConfig_la_MOC) \
			ClipConfigFile.cpp \
			ClipProfile.cpp \
			ConfigFile.cpp \
			SimpleConfigFile.cpp

EXTRA_DIST = ClipConfig.pc.in 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ClipConfig.pc 

AM_CXXFLAGS = $(QT4_CORE_CFLAGS) $(QT4_GUI_CFLAGS)
libClipConfig_la_LDFLAGS = -version-info @CLIPCONFIG_VERSION_INFO@ $(QT4_CORE_LIBS) $(QT4_GUI_LIBS)

INCLUDES = -I$(srcdir) 

%.moc.cpp: %.h Makefile
	moc -o $@ $<

