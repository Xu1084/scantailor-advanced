// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#ifndef SCANTAILOR_CORE_UNITS_H_
#define SCANTAILOR_CORE_UNITS_H_


#include <QtCore/QString>

enum Units { PIXELS, MILLIMETRES, CENTIMETRES, INCHES };

QString unitsToString(Units units);

Units unitsFromString(const QString& string);

QString unitsToLocalizedString(Units units);

#endif  // SCANTAILOR_CORE_UNITS_H_
