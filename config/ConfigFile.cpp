// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file ConfigFile.cpp
 * ClipConfig configuration file abstraction.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include "ConfigFile.h"
#include "CCException.h"
#include <QFile>
#include <QTextStream>


ConfigFile::ConfigFile(void)
{
  worldReadable = false;
}

void
ConfigFile::setPublic()
{
  worldReadable = true;
}

void 
ConfigFile::readFile(const QString& fn)
{
  filename = fn;
  QFile f(filename);
  resetContent();

  if (f.open(QIODevice::ReadOnly)) {
    QTextStream s(&f);
    s.setCodec("UTF-8");
    QString line;

    while (!(line = s.readLine()).isNull())
      readLine(line);
  }
}

QString 
ConfigFile::getVal() const
{
  throw CCException ("ConfigFile::getVal should have been overloaded");
}

void 
ConfigFile::setVal(const QString& val)
{
  throw CCException ("ConfigFile::setVal should have been overloaded");
}

QString 
ConfigFile::getNameVal(const QString& vname, const QRegExp& filter) const
{
  throw CCException ("ConfigFile::getNameVal should have been overloaded");
}

void 
ConfigFile::setNameVal(const QString& vname, const QString& val)
{
  throw CCException ("ConfigFile::setNameVal should have been overloaded");
}

QString 
ConfigFile::getIndexVal(int ni, const QRegExp& filter) const
{
  throw CCException ("ConfigFile::getIndexVal should have been overloaded");
}

void 
ConfigFile::setIndexVal(int n, const QString& val)
{
  throw CCException ("ConfigFile::setIndexVal should have been overloaded");
}

void 
ConfigFile::writeFile() 
{
  if (filename.isEmpty ())
    throw CCException ("ConfigFile::writeFile called without a filename");
  QFile f(filename);
  const QStringList content = contentToWrite();

  if (f.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
    QTextStream s(&f);
    s.setCodec("UTF-8");
    QStringList::const_iterator i;

    for (i = content.constBegin(); i != content.constEnd(); ++i) {
      s << *i << '\n';
    }
    if (worldReadable) {
      f.setPermissions(QFile::WriteOwner | QFile::ReadOwner | QFile::ReadGroup | QFile::ReadOther);
    }
  } else {
    throw CCException("ConfigFile::writeFile could not write " + filename);
  }
}

void
ConfigFile::writeFileAs(const QString& fn)
{
  filename = fn;
  writeFile();
}

// vi:sw=2:ts=2:et:co=80:
