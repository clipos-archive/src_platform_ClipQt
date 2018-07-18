// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright © 2010-2018 ANSSI. All Rights Reserved.
/**
 * @file CCException 
 * ClipConfig exceptions.
 * @author Olivier Levillain <clipos@ssi.gouv.fr>
 * @author Vincent Strubel <clipos@ssi.gouv.fr>
 *
 * Copyright (C) 2009 SGDN
 * Copyright (C) 2010 ANSSI
 * @n
 * All rights reserved.
 */

#ifndef CLIP_CONFIG_CCEXCEPTION_H
#define CLIP_CONFIG_CCEXCEPTION_H

#include <QString>

class CCException {
 private:
  const QString reason;
 public:
  CCException(const QString& reason)
    : reason(reason) { qDebug("CCException: %s\n", reason.toStdString().c_str());}
  const char* const toString() const
	  {return reason.toStdString().c_str(); };
};

#endif // CLIP_CONFIG_CCEXCEPTION_H
