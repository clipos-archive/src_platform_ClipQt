// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file ClipProfile.h
 * ClipConfig configuration profile header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIP_CONFIG_CLIPPROFILE_H
#define CLIP_CONFIG_CLIPPROFILE_H

#include "SimpleConfigFile.h"
#include "ClipConfigFile.h"

#include <QMap>

class ClipProfile 
{
 public:
  ClipProfile(const QString& baseName, const QString& dirName);
  ~ClipProfile();

  virtual bool createSubDirs() {return true;};
  virtual bool removeSubDirs() {return true;};
  bool addFile(int where, ConfigFile *what);

  QString getVal(int where) const;
  void setVal(int where, const QString& val);

  QString getNameVal(int where, 
                  const QString& vname, const QRegExp& filter) const;
  void setNameVal(int where, 
                  const QString& vname, const QString& val);

  QString getIndexVal(int where, int ni, 
                            const QRegExp &filter = QRegExp()) const;
  void setIndexVal(int where, int n, const QString& val);

  const QString& getProfileName() { return profileName; }
  bool pendingChanges();
  bool isValid() { return valid; };
  void setValid(bool val) { valid = val; };
  void writeProfile();
  void writeProfileAs(const QString& baseName, const QString& dirName);
  void inheritProfileAs(const QString& baseName, const QString& dirName);
  bool deleteProfile();
  void inheritFile(int where, const QString& parentPath);
  void disinheritFile(int where);
  QString inheritsFrom(int where);

 protected:
  QString profileName;
  QString path;
  bool valid;

 private:
  QMap<int, ConfigFile *> files;
  void cloneProfileAs(const QString& baseName, const QString& dirName,
      bool inherit);
};

#endif // CLIP_CONFIG_CLIPPROFILE_H

// vi:sw=2:ts=2:et:co=80: 
