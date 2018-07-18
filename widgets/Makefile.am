# SPDX-License-Identifier: LGPL-2.1-or-later
# Copyright © 2010-2018 ANSSI. All Rights Reserved.

lib_LTLIBRARIES = libClipWidgets.la

libClipWidgetsincludedir = $(includedir)/clip/ClipWidgets
libClipWidgetsinclude_HEADERS = \
			IPField.h \
			LabelledField.h \
			MultiField.h \
			WaitDialog.h

libClipWidgets_la_MOC = \
			IPField.moc.cpp \
			LabelledField.moc.cpp \
			MultiField.moc.cpp \
			WaitDialog.moc.cpp

libClipWidgets_la_SOURCES = \
			$(libClipWidgets_la_MOC) \
			IPField.cpp \
			LabelledField.cpp \
			MultiField.cpp \
			WaitDialog.cpp

BUILT_SOURCES = $(libClipWidgets_la_MOC)

EXTRA_DIST = ClipWidgets.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ClipWidgets.pc

AM_CXXFLAGS = $(QT4_CORE_CFLAGS) $(QT4_GUI_CFLAGS)
libClipWidgets_la_LDFLAGS = -version-info @CLIPWIDGETS_VERSION_INFO@ $(QT4_CORE_LIBS) $(QT4_GUI_LIBS)

INCLUDES = -I$(srcdir) 

%.moc.cpp: %.h Makefile
	moc -o $@ $<

