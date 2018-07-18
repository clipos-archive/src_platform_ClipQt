// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file WaitDialog.h
 * ClipWidgets wait form header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIPWIDGETS_WAITDIALOG_H
#define CLIPWIDGETS_WAITDIALOG_H

#include <QDialog>

class QProcess;
class QKeyEvent;
class QCloseEvent;

class WaitDialog : public QDialog
{
  Q_OBJECT

 public:
  WaitDialog(const QString& title, const QString& msg, const bool& ptrFinished);
  WaitDialog(const QString& title, const QString& msg, QProcess& p);

 protected:
  virtual void keyPressEvent(QKeyEvent *e);
  virtual void closeEvent(QCloseEvent *e);

 private:
  const bool* finished;
  QProcess* runningProcess;
  void init(const QString& title, const  QString& msg);
};

#endif // CLIPWIDGETS_WAITDIALOG_H

// vi:sw=2:ts=2:et:co=80:
