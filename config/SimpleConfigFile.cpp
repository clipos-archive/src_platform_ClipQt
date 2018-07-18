// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file SimpleConfigFile.cpp
 * ClipConfig simple configuration file.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#include "SimpleConfigFile.h"

void 
SimpleConfigFile::resetContent() 
{
  content.clear();
}

void 
SimpleConfigFile::readLine(const QString& line) 
{
  content.append(line);
}

bool 
SimpleConfigFile::pendingChanges() const 
{
  return isModified;
}

const QStringList 
SimpleConfigFile::contentToWrite() 
{
  isModified = false;
  return content;
}

QString 
SimpleConfigFile::getVal() const
{
  return content.join("\n");
}

void
SimpleConfigFile::setVal(const QString& val)
{
  //content = val.split("\n");
  QStringList value = val.split("\n");
  if (value != content) {
    isModified = true;
    content = value;
  }
}

// vi:sw=2:ts=2:et:co=80: 
