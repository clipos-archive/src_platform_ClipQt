// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file IPField.h
 * clip-config IP full address field (IP + mask) header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIPWIDGETS_IPFIELD_H
#define CLIPWIDGETS_IPFIELD_H

#include <QFrame>
#include <QLineEdit>

class QKeyEvent;

class IPElt : public QLineEdit
{
  Q_OBJECT
 public:
  IPElt (QWidget* parent);
  void setNameValue (unsigned char n);
  void setNext (QLineEdit* n, char separator);

 protected:
  virtual void keyPressEvent (QKeyEvent* e); 

 private:
  char sep;
  QLineEdit* next;
};

class IPField : public QFrame
{
    Q_OBJECT

 public:
  IPField (QWidget* parent, const QString& lbl, 
          int left = 10, int right = 10, bool addMaskField = false);

  void setNameValue(const QString& ip, const QString& mask = QString());
  const QString returnIP() const;
  const QString returnMask() const;

 private:
  IPElt* fields[4];
  QLineEdit* maskField;
};


#endif // CLIPWIDGETS_IPFIELD_H

// vi:sw=2:ts=2:et:co=80:
