// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file MultiField.h
 * ClipWidgets generic multiple field header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIPWIDGETS_MULTIFIELD_H
#define CLIPWIDGETS_MULTIFIELD_H

#include <QFrame>
#include <QRegExp>

class QPushButton;
class QListWidget;
class QLineEdit;

class MultiField : public QFrame
{
  Q_OBJECT

 public:
  MultiField(QWidget* parent, const QString& lbl,
             const QRegExp& elt, const QString& sep,
             int width, int height,
             bool vertLayout = false,
             const QString& lbl2 = QString(""));
             
  virtual void setValue(const QString& vals);
  virtual const QString returnValues() const;
  virtual bool changesPending() const {return modified;};

 protected:
  virtual void addValue(const QString& p);
  QString originalValue;
  QString separator;
  QRegExp regexp;
  bool modified;

  QPushButton *btnAdd;
  QPushButton *btnDel;

  QListWidget *values;
  QLineEdit *valueToAdd;

 protected slots:
  void btnAddClicked();
  void btnDelClicked();
};

#endif // CLIPWIDGETS_MULTIFIELD_H

// vi:sw=2:ts=2:et:co=80:
