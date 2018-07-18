// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file ClipConfigFile.h
 * ClipConfig multi-variable configuration file header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIP_CONFIG_CLIPCONFIGFILE_H
#define CLIP_CONFIG_CLIPCONFIGFILE_H

#include <QLinkedList>

#include "ConfigFile.h"

class ClipConfigFileLine 
{
 public:  
  ClipConfigFileLine(const QString& q);
  ClipConfigFileLine(const QString& line, const QString& q);
  ClipConfigFileLine(const QString& vname, 
                      const QString& val, const QString& q);

  bool getNameVal(const QString& vname, 
                          QString& res, const QRegExp& filter) const;
  bool setNameVal(const QString& vname, const QString& val);

  const QString& getLineAndReset();
  bool pendingChange() const;

 private:
  QString quotes;
  QString varname;
  QString value;
  QString rawline;
  
  QString originalValue;
  bool isModified;
  bool isNew;
};

class ClipConfigFile : public ConfigFile 
{
 public:
  virtual QString getNameVal(const QString& vname, const QRegExp& filter) const;
  virtual void setNameVal(const QString& vname, const QString& val);

  virtual bool pendingChanges() const;

 protected:
  virtual void resetContent();
  virtual void readLine(const QString& line);
  virtual const QStringList contentToWrite();  

 private:
  QLinkedList<ClipConfigFileLine> content;
};

#endif // CLIP_CONFIG_CLIPCONFIGFILE_H

// vi:sw=2:ts=2:et:co=80:
