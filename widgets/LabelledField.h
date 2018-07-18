// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file LabelledField.h
 * ClipWidgets simple labelled field header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN/DCSSI
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIPWIDGETS_LABELLEDFIELD_H
#define CLIPWIDGETS_LABELLEDFIELD_H

#include <QFrame>

class LabelledField : public QFrame
{
  Q_OBJECT

 public:
  LabelledField(QWidget* parent, const QString& lbl, 
                QWidget* w, int left = 10, int right = 10);
  LabelledField(QWidget* parent, QWidget* w, 
                int left = 10, int right = 10);
  LabelledField(QWidget* parent, const QString& lbl, 
                int left = 10, int right = 10);
};

#endif // CLIPWIDGETS_LABELLEDFIELD_H

// vi:sw=2:ts=2:et:co=80:
