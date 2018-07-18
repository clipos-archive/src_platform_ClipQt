// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file ClipProfile.cpp
 * ClipConfig configuration profile.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include "ClipProfile.h"
#include "CCException.h"

#include <QDir>

static const QRegExp profileName_rx("[0-9a-zA-Z_\\-]+");

ClipProfile::ClipProfile(const QString& baseName, const QString& dirName)
  : profileName(baseName), valid(true)
{
  if (!profileName_rx.exactMatch(baseName))
    throw CCException(QString("ClipProfile cannot handle the "
                              "profile named ") + baseName);

  QDir dir;
  path = dirName + "/" + baseName;

  if (!(dir.exists(path) || dir.mkdir(path)) || !createSubDirs())
    throw CCException(QString("ClipProfile couldn't open or create profile "
                              "directory for the profile named %1")
                              .arg(baseName));
}

ClipProfile::~ClipProfile() 
{
  QMap<int, ConfigFile *>::iterator f = files.begin();
  while (f != files.end()) {
    delete f.value();
    f++;
  }
}

bool
ClipProfile::addFile(int where, ConfigFile *what)
{
  if (files.contains(where)) {
    qDebug("ClipProfile already has a file at index %d", where);
    return false;
  }

  files.insert(where, what);
  return true;
}

QString 
ClipProfile::getVal(int where) const
{
  if (!files.contains(where))
    throw CCException(QString("ClipProfile::getVal called with "
                          "an incorrect parameter where (%1).").arg(where));

  return files[where]->getVal();
}

void 
ClipProfile::setVal(int where, const QString& val) 
{
  if (!files.contains(where))
    throw CCException(QString("ClipProfile::setVal called with "
                              "an incorrect parameter where (%1).").arg(where));

  files[where]->setVal(val);
}


QString 
ClipProfile::getNameVal(int where, 
              const QString& vname, const QRegExp& filter) const 
{
  if (!files.contains(where))
    throw CCException(QString("ClipProfile::getNameVal called with "
                          "an incorrect parameter where (%1).").arg(where));

  return files[where]->getNameVal(vname, filter);
}

void 
ClipProfile::setNameVal(int where, const QString& vname, const QString& val) 
{
  if (!files.contains(where))
    throw CCException(QString("ClipProfile::setNameVal called with "
                              "an incorrect parameter where (%1).").arg(where));

  files[where]->setNameVal(vname, val);
}

QString 
ClipProfile::getIndexVal(int where, int ni, const QRegExp& re) const 
{
  if (!files.contains(where))
    throw CCException(QString("ClipProfile::getNS called with "
                              "an incorrect parameter where (%1).").arg(where));

  return files[where]->getIndexVal(ni, re);
}

void 
ClipProfile::setIndexVal(int where, int n, const QString& val) 
{
  if (!files.contains(where))
    throw CCException(QString("ClipProfile::setNS called with "
                              "an incorrect parameter where (%1).").arg(where));

  files[where]->setIndexVal(n, val);
}

bool 
ClipProfile::pendingChanges() 
{
  QMap<int, ConfigFile *>::iterator f = files.begin();
  while (f != files.end()) {
    if (f.value()->pendingChanges())
      return true;
    f++;
  }
  return false;
}

void 
ClipProfile::writeProfile() 
{
  if (!isValid())
    return; // Do not save an incorrect / incomplete profile
  QMap<int, ConfigFile *>::iterator f = files.begin();
  while (f != files.end()) {
    // Only write if it is not an inherited file
    if (inheritsFrom(f.key()).isEmpty())
      f.value()->writeFile();
    f++;
  }
}

void 
ClipProfile::writeProfileAs(const QString& baseName, const QString& dirName)
{
  cloneProfileAs(baseName, dirName, false);
}

void
ClipProfile::inheritProfileAs(const QString& baseName, const QString& dirName)
{
  cloneProfileAs(baseName, dirName, true);
}

void 
ClipProfile::cloneProfileAs(const QString& baseName, const QString& dirName,
    bool inherit)
{
  QDir dir;

  if (!isValid())
    return;

  if (!profileName_rx.exactMatch(baseName))
    throw CCException(QString("ClipProfile can not handle the "
                              "profile named ") + baseName);

  QString newpath = dirName + "/" + baseName;

  if (!dir.exists(newpath) && dir.mkdir(newpath)) {
    profileName = baseName;
    QString oldpath = path;
    path = newpath;

    if (!createSubDirs())
      throw CCException(QString("ClipProfile couldn't create subdirectories "
                              "for the profile named %1")
                              .arg(baseName));

    QMap<int, ConfigFile *>::iterator f = files.begin();
    while (f != files.end()) {
      QString fpath = f.value()->name();
      fpath.replace(oldpath, path);

      f.value()->writeFileAs(fpath);
      if (inherit)
        inheritFile(f.key(), oldpath);
      f++;
    }
  } else {
    throw CCException(QString("ClipProfile couldn't create profile "
                              "directory for the profile named %1")
                              .arg(baseName));
  }
}

bool 
ClipProfile::deleteProfile() 
{
  QDir dir;

  QMap<int, ConfigFile *>::iterator f = files.begin();
  while (f != files.end()) {
    QFile::remove(f.value()->name());
    f++;
  }
  if (!removeSubDirs())
    return false;
  return dir.rmdir(path);
}

void
ClipProfile::inheritFile(int where, const QString &parentPath)
{
  if (!inheritsFrom(where).isEmpty())
    return; // Already inherited

  // Absolute path+filename of the to-be-inherited file
  QString child = files[where]->name();
  QFile::remove(child);

  // Absolute path of the directory containing the to-be-inherited file
  QDir childDir = QFileInfo(child).dir();

  // Absolute path+filename of the parent file
  QString parentFile = QString(child);
  parentFile.replace(path, parentPath);

  // Compute the relative path of the parent from the child's directory
  QString relPath = childDir.relativeFilePath(parentFile);

  QFile::link(relPath, child);
  // load the newly pointed-to file
  files[where]->readFile(child);
}

void
ClipProfile::disinheritFile(int where)
{
  QString parent = inheritsFrom(where);
  if (parent.isEmpty())
    return;

  QString child = files[where]->name();
  QFile::remove(child);
  QFile::copy(parent, child);
}

QString
ClipProfile::inheritsFrom(int where)
{
  return QFile::symLinkTarget(files[where]->name());
}

// vi:sw=2:ts=2:et:co=80: 
