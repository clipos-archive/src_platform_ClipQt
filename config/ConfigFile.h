// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file ConfigFile.h
 * ClipConfig configuration file abstraction header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIP_CONFIG_CONFIGFILE_H
#define CLIP_CONFIG_CONFIGFILE_H

#include <QStringList>

class ConfigFile 
{
 public:
  ConfigFile();

  void readFile(const QString& filename);

  virtual QString getVal() const;
  virtual void setVal(const QString& val);

  virtual QString getNameVal(const QString& vname, const QRegExp& filter) const;
  virtual void setNameVal(const QString& vname, const QString& val);

  virtual QString getIndexVal(int ni, const QRegExp& filter = QRegExp()) const;
  virtual void setIndexVal(int n, const QString& val);

  void setQuotes(const QString &q) { quotes = q; };

  virtual bool pendingChanges() const = 0;
  void writeFile();
  void writeFileAs(const QString& filename);
  void setPublic(void);

  QString name() const { return filename; };

 protected:
  virtual void resetContent() = 0;
  virtual void readLine(const QString& line) = 0;
  virtual const QStringList contentToWrite() = 0;
  QString quotes;

 private:
  QString filename;
  bool worldReadable;
};

#endif // CLIP_CONFIG_CONFIGFILE_H

// vi:sw=2:ts=2:et:co=80:
