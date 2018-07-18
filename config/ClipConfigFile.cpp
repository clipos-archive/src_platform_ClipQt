// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file ClipConfigFile.cpp
 * ClipConfig multi-variable configuration file.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include <QRegExp>

#include "ClipConfigFile.h"

static const QRegExp varname_rx("\\w+");

ClipConfigFileLine::ClipConfigFileLine(const QString& q) 
{
  isModified = isNew = false;
  quotes = q;
  rawline = originalValue = QString();
}

ClipConfigFileLine::ClipConfigFileLine(const QString& vname, 
                                      const QString& val, const QString &q)
{
  quotes = q;
  varname = vname;
  value = val;
  rawline = varname + "=" + value;
  isNew = isModified = true;
}

ClipConfigFileLine::ClipConfigFileLine (const QString& line, const QString& q) 
{
  quotes = q;
  int index = line.indexOf('=');
  
  if (index != -1) {
    QString vn = line.left(index);
    if (varname_rx.exactMatch(vn)) {
      varname = vn;
      value = line.mid(index+1);      
    }
    if (value.isNull())
      value = QString("");
    else if (!quotes.isEmpty()) {
      if (value.endsWith(quotes))
        value.chop(quotes.length());
      if (value.startsWith(quotes))
        value = value.mid(quotes.length());
    }
    originalValue = QString(value);
  }

  rawline = line;
  isModified = isNew = false;
}

bool 
ClipConfigFileLine::getNameVal(const QString& vname, QString& res, 
                           const QRegExp& filter) const
{
  if (vname != varname)
    return false;

  int index = filter.indexIn(value);
  if (index == -1)
    res = QString();
  else
    res = value.mid(index, filter.matchedLength());
  return true;
}

bool 
ClipConfigFileLine::setNameVal(const QString& vname, const QString& val)
{
  if (vname != varname) 
    return false;

  value = val;
  rawline = varname + "=" + quotes + value + quotes; 
  isModified = (value != originalValue);
  return true;
}

const QString& 
ClipConfigFileLine::getLineAndReset() 
{
  originalValue = value;
  isModified = false;
  isNew = false;
  return rawline;
}

bool 
ClipConfigFileLine::pendingChange() const 
{
#if 0
  if (isNew)
    qDebug("  Line added: \"%s\"", (const char*) rawline);
  else if (isModified)
    qDebug ("  Variable %s modifed from \"%s\" to \"%s\"", 
      varname.toStdString().c_str(), originalValue.toStdString().c_str(), 
      value.toStdString().c_str());
#endif

  return isModified || isNew;
}

void 
ClipConfigFile::resetContent() 
{
  content.clear();
}

void 
ClipConfigFile::readLine(const QString& line)
{
  content.append(ClipConfigFileLine(line, quotes));
}

QString 
ClipConfigFile::getNameVal(const QString& vname, const QRegExp& filter) const 
{
  QLinkedList<ClipConfigFileLine>::const_iterator i;
  QString res;

  for (i = content.constBegin(); i != content.constEnd(); ++i) {
    if ((*i).getNameVal(vname, res, filter))
      return res;
  }

  return QString();
}

void 
ClipConfigFile::setNameVal(const QString& vname, const QString& val) 
{
  QLinkedList<ClipConfigFileLine>::iterator i;

  for (i = content.begin(); i != content.end(); ++i) {
    if ((*i).setNameVal(vname, val))
      return;
  }

  content.append(ClipConfigFileLine(vname, val, quotes));
}

bool 
ClipConfigFile::pendingChanges() const 
{
  QLinkedList<ClipConfigFileLine>::const_iterator i;

  //qDebug("Checking changes in %s:\n", (const char*) filename);
  for (i=content.constBegin(); i!=content.constEnd(); ++i) {
    if ((*i).pendingChange())
      return true;
  }

  return false;
}

const QStringList 
ClipConfigFile::contentToWrite() 
{
  QStringList res;
  QLinkedList<ClipConfigFileLine>::iterator i;
  for (i = content.begin(); i != content.end(); ++i)
    res.append((*i).getLineAndReset());
  return res;
}

// vi:sw=2:ts=2:et:co=80:
