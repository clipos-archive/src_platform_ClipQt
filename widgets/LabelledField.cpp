// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file LabelledField.cpp
 * ClipWidgets simple labelled field.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN/DCSSI
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include <QLabel>
#include <QLayout>

#include "LabelledField.h"

LabelledField::LabelledField(QWidget* parent, const QString& lbl, 
            QWidget* w, int left, int right)
  : QFrame(parent)
{
  QHBoxLayout* layout = new QHBoxLayout(this);

  layout->addSpacing(left);
  layout->addWidget(new QLabel(lbl + " : ", this));
  //w->reparent(this, w->pos());
  layout->addStretch(2);
  layout->addWidget(w);
  layout->addSpacing(right);
}


LabelledField::LabelledField (QWidget* parent, QWidget* w, int left, int right)
  : QFrame(parent)
{
  QHBoxLayout* layout = new QHBoxLayout(this);

  layout->addSpacing(left);
  //w->reparent(this, w->pos());
  layout->addWidget(w);
  layout->addStretch(2);
  layout->addSpacing(right);
}


LabelledField::LabelledField (QWidget* parent, const QString& lbl, 
            int left, int right)
  : QFrame(parent)
{
  QHBoxLayout* layout = new QHBoxLayout(this);

  layout->addSpacing(left);
  layout->addWidget(new QLabel(lbl + " : ", this));
  layout->addStretch(2);
  layout->addSpacing(right);
}

// vi:sw=2:ts=2:et:co=80:
