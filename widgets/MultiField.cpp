// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file MultiField.cpp
 * ClipWidgets generic multiple field.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include "MultiField.h"

#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QLayout>
#include <QValidator>
#include <QPalette>
#include <QPushButton>


MultiField::MultiField(QWidget* parent, const QString& lbl, 
                       const QRegExp& re, const QString& sep,
                       int width, int height,
                       bool vertLayout, const QString &lbl2)
  : QFrame(parent), separator(sep), regexp(re)
{
  values = new QListWidget(this);
  values->setSelectionMode(QAbstractItemView::MultiSelection);
  values->setFixedWidth(width);
  values->setMaximumHeight(height);
  QPalette pal = values->palette();
  pal.setColor(QPalette::Disabled, QPalette::Base,
               pal.color(QPalette::Disabled, QPalette::Window));
  values->setPalette(pal);

  valueToAdd = new QLineEdit(this);
  valueToAdd->setFixedWidth(width);
  valueToAdd->setValidator(new QRegExpValidator(re, this));
  valueToAdd->setToolTip("Saisissez une valeur, puis cliquez sur :\n"
                         "+ pour ajouter à la liste\n"
                         " - pour supprimer de la liste");

  btnAdd = new QPushButton ("+", this);
  btnAdd->setMaximumWidth(25);
  btnAdd->setMaximumHeight(25);
  btnDel = new QPushButton ("-", this);
  btnDel->setMaximumWidth(25);
  btnDel->setMaximumHeight(25);

  connect (valueToAdd, SIGNAL(returnPressed()), this, SLOT(btnAddClicked()));
  connect (btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
  connect (btnDel, SIGNAL(clicked()), this, SLOT(btnDelClicked()));

  if (vertLayout) {
    QVBoxLayout* lv2 = new QVBoxLayout();
    lv2->addWidget(valueToAdd);

    QHBoxLayout* lbuttons = new QHBoxLayout();
    lbuttons->addStretch(2);
    lbuttons->addWidget(btnAdd);
    lbuttons->addStretch(2);
    lbuttons->addWidget(btnDel);
    lbuttons->addStretch(2);
    lv2->addLayout(lbuttons);
    lv2->addSpacing(20);
    lv2->addStretch(2);

    QHBoxLayout* lh1 = new QHBoxLayout();
    lh1->addStretch(2);
    lh1->addWidget(values);
    lh1->addStretch(2);

    QHBoxLayout* lh2 = new QHBoxLayout();
    lh2->addStretch(2);
    lh2->addWidget(new QLabel(lbl2, this));
    lh2->addStretch(2);

    QHBoxLayout* lh3 = new QHBoxLayout();
    lh3->addStretch(2);
    lh3->addLayout(lv2);
    lh3->addStretch(2);

    QVBoxLayout* lv = new QVBoxLayout(this);
    QHBoxLayout* lt = new QHBoxLayout();
    lt->addSpacing(30);
    lt->addWidget(new QLabel (lbl + " : ", this));
    lt->addStretch(2);
    lv->addLayout(lt);
    lv->addSpacing(5);
    lv->addLayout(lh1);
    lv->addSpacing(5);
    lv->addLayout(lh2);
    lv->addSpacing(5);
    lv->addLayout (lh3);
  } else {
    QVBoxLayout* lv2 = new QVBoxLayout();
    lv2->addWidget(valueToAdd);
    QHBoxLayout* lbuttons = new QHBoxLayout();
    lbuttons->addStretch(2);
    lbuttons->addWidget(btnAdd);
    lbuttons->addStretch(2);
    lbuttons->addWidget(btnDel);
    lbuttons->addStretch(2);
    lv2->addLayout(lbuttons);
    lv2->addSpacing(20);
    lv2->addStretch(2);

    QHBoxLayout* lh = new QHBoxLayout();
    lh->addStretch(2);
    lh->addWidget(values);
    lh->addStretch(2);
    lh->addLayout(lv2);
    lh->addStretch(2);

    QVBoxLayout* lv = new QVBoxLayout(this);
    lv->addWidget(new QLabel(lbl + " : ", this));
    lv->addLayout(lh);
  }
}

void 
MultiField::setValue(const QString& vals) 
{
  QStringList tmp = vals.split(separator);
  QStringList::const_iterator i;

  values->clear();
  for (i = tmp.constBegin(); i != tmp.constEnd(); ++i)
    addValue(*i);

  originalValue = vals.isEmpty() ? QString ("-") : vals;
  modified = false;
}

void 
MultiField::addValue(const QString& a) 
{
  if (!regexp.exactMatch(a))
    return;

  values->insertItem(0, a);
  //values->setCurrentRow(0);
  modified = true;
}

void 
MultiField::btnAddClicked() 
{
  addValue(valueToAdd->text());
  valueToAdd->setText("");
  valueToAdd->setFocus();
}

void 
MultiField::btnDelClicked() 
{
  int i = 0;
  QListWidgetItem *it;

  while ((it = values->item(i)) != 0) {
    if (it->isSelected()) {
      delete it;
      modified = true;
    }
    else
      i++;
  }
}

const QString 
MultiField::returnValues() const 
{
  if (!modified)
    return originalValue;

  bool first = true;
  int i = 0;
  QString res;
  QListWidgetItem *it;

  while ((it = values->item(i)) != 0) {
    if (!first) 
      res += separator;
    first = false;
    res += it->text();
    ++i;
  }

  if (first)
    return QString("-");
  else
    return res;
}

// vim:sw=2:ts=2:et:co=80:
