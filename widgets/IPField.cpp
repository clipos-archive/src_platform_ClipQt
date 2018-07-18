// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file IPField.cpp
 * clip-config full IP address (IP + mask) field.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include "IPField.h"

#include <QLabel>
#include <QValidator>
#include <QApplication>
#include <QLayout>
#include <QKeyEvent>

IPElt::IPElt(QWidget* parent)
  : QLineEdit("0", parent)
{
  setValidator(new QIntValidator(0, 255, this));
  setMaximumWidth(45);
}

void 
IPElt::setNameValue(unsigned char n) 
{
  setText(QString::number(n));
}

void 
IPElt::setNext(QLineEdit* n, char separator) 
{
  next = n;
  sep = separator;
}

void 
IPElt::keyPressEvent(QKeyEvent* e) 
{
  QString touche = e->text();

  if (touche[0] == ' ' || touche[0] == sep) {
    if (next) {
      next->setFocus();
      next->selectAll();
    }
    e->accept();
    return;
  }

  if (touche[0] <= '9' && touche[0] >= '0' 
            && !hasSelectedText() && text().length() == 3 
            && cursorPosition() == 3 && next) {
    next->setFocus();
    next->selectAll();
    QApplication::sendEvent(next, e);
    return;
  }

  QLineEdit::keyPressEvent(e); 
}


IPField::IPField (QWidget* parent, const QString& lbl, 
              int left, int right, bool addMaskField)
  : QFrame(parent)
{
  int i;
  QHBoxLayout* layout = new QHBoxLayout(this);

  layout->addSpacing(left);
  layout->addWidget(new QLabel(lbl + " : ", this));
  layout->addStretch(2);

  for (i = 0; i < 4; i++) {
    layout->addWidget(fields[i] = new IPElt(this));
      if (i < 3) 
        layout->addWidget(new QLabel(".", this));
  }

  for (i = 0; i < 3; i++)
    fields[i]->setNext(fields[i+1], '.');

  if (addMaskField) {
    layout->addWidget(new QLabel(" / ", this));
    layout->addWidget(maskField = new QLineEdit("0", this));
    maskField->setValidator(new QIntValidator(0, 32, this));
    maskField->setMaximumWidth(30);
    fields[3]->setNext(maskField, '/');
  } else 
    maskField = 0;

  layout->addSpacing(right);
}

void 
IPField::setNameValue(const QString& ip, const QString& mask) 
{
  int i;
  QStringList tmp = ip.split('.');
  bool correct_input = tmp.size() == 4;
  for (i = 0; i < 4; i++)
    fields[i]->setNameValue(correct_input ? tmp[i].toUShort() : 0);

  if (maskField) {
    int maskval = (mask != 0) ? mask.toUShort() : 0;
    if (maskval < 0 && maskval > 32)
      maskval = 0;
    maskField->setText(QString::number(maskval));
  }
}

const QString 
IPField::returnIP() const 
{
  QString res;
  for (int i = 0; i < 4; i++) {
    res += QString::number(fields[i]->text().toInt());
    if (i < 3) 
      res += '.';
  }
  return res;
}

const QString 
IPField::returnMask() const 
{
  if (maskField)
    return maskField->text();
  return "";
}

// vi:sw=2:ts=2:et:co=80:
