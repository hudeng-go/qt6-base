/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/qglobal.h>

// SCENARIO 4
// this is the "full" version. Operator+ is replaced by a QStringBuilder
// based version
// with NO_CAST * _not_ defined
#define QT_USE_QSTRINGBUILDER
#undef QT_NO_CAST_FROM_ASCII
#undef QT_NO_CAST_TO_ASCII

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringBuilder>
#include <QtTest/QTest>

#define LITERAL "some literal"

void runScenario(); // Defined in stringbuilder.cpp #included below.

class tst_QStringBuilder4 : public QObject
{
    Q_OBJECT

private slots:
    void scenario() { runScenario(); }
};

#define P +
#include "../qstringbuilder1/stringbuilder.cpp"
#undef P

#include "tst_qstringbuilder4.moc"

QTEST_APPLESS_MAIN(tst_QStringBuilder4)
