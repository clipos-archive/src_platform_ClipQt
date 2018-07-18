// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file SimpleConfigFile.h
 * ClipConfig simple configuration file header.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIP_CONFIG_SIMPLECONFIGFILE_H
#define CLIP_CONFIG_SIMPLECONFIGFILE_H

#include "ConfigFile.h"

class SimpleConfigFile : public ConfigFile 
{
 public:
  virtual bool pendingChanges() const;
  virtual QString getVal() const;
  virtual void setVal(const QString& val);

 protected:
  virtual void resetContent();
  virtual void readLine(const QString& line);
  virtual const QStringList contentToWrite();  

 private:
  QStringList content;
  bool isModified;
};

#endif // CLIP_CONFIG_SIMPLECONFIGFILE_H

// vi:sw=2:ts=2:et:co=80:
