/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QString>
#include <QDBusArgument>
#include <QDBusMetaType>
#include <QDBusMessage>
#include <QDBusContext>

typedef QDBusVariant MyElement;
typedef QList<MyElement> MyArray;
typedef QHash<int, MyElement> MyDictionary;
typedef QDBusVariant MyType;
typedef QDBusVariant MyValue;
typedef QDBusVariant Type;
QDBusArgument argument;

class MyObject: public QObject
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "org.qtproject.QtDBus.MyObject")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.qtproject.QtDBus.MyObject\" >\n"
"    <property access=\"readwrite\" type=\"i\" name=\"prop1\" />\n"
"    <property name=\"complexProp\" type=\"ai\" access=\"readwrite\">\n"
"      <annotation name=\"org.qtproject.QtDBus.QtTypeName\" value=\"QList&lt;int&gt;\"/>\n"
"    </property>\n"
"    <signal name=\"somethingHappened\" >\n"
"      <arg direction=\"out\" type=\"s\" />\n"
"    </signal>\n"
"    <method name=\"ping\" >\n"
"      <arg direction=\"in\" type=\"v\" name=\"ping\" />\n"
"      <arg direction=\"out\" type=\"v\" name=\"ping\" />\n"
"    </method>\n"
"    <method name=\"ping_invokable\" >\n"
"      <arg direction=\"in\" type=\"v\" name=\"ping_invokable\" />\n"
"      <arg direction=\"out\" type=\"v\" name=\"ping_invokable\" />\n"
"    </method>\n"
"    <method name=\"ping\" >\n"
"      <arg direction=\"in\" type=\"v\" name=\"ping1\" />\n"
"      <arg direction=\"in\" type=\"v\" name=\"ping2\" />\n"
"      <arg direction=\"out\" type=\"v\" name=\"pong1\" />\n"
"      <arg direction=\"out\" type=\"v\" name=\"pong2\" />\n"
"    </method>\n"
"    <method name=\"ping_invokable\" >\n"
"      <arg direction=\"in\" type=\"v\" name=\"ping1_invokable\" />\n"
"      <arg direction=\"in\" type=\"v\" name=\"ping2_invokable\" />\n"
"      <arg direction=\"out\" type=\"v\" name=\"pong1_invokable\" />\n"
"      <arg direction=\"out\" type=\"v\" name=\"pong2_invokable\" />\n"
"    </method>\n"
"    <method name=\"ping\" >\n"
"      <arg direction=\"in\" type=\"ai\" name=\"ping\" />\n"
"      <arg direction=\"out\" type=\"ai\" name=\"ping\" />\n"
"      <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"QList&lt;int&gt;\"/>\n"
"      <annotation name=\"org.qtproject.QtDBus.QtTypeName.Out0\" value=\"QList&lt;int&gt;\"/>\n"
"    </method>\n"
"    <method name=\"ping_invokable\" >\n"
"      <arg direction=\"in\" type=\"ai\" name=\"ping_invokable\" />\n"
"      <arg direction=\"out\" type=\"ai\" name=\"ping_invokable\" />\n"
"      <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"QList&lt;int&gt;\"/>\n"
"      <annotation name=\"org.qtproject.QtDBus.QtTypeName.Out0\" value=\"QList&lt;int&gt;\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
    Q_PROPERTY(int prop1 READ prop1 WRITE setProp1)
    Q_PROPERTY(QList<int> complexProp READ complexProp WRITE setComplexProp)

public:
    static int callCount;
    static QVariantList callArgs;
    MyObject()
    {
        QObject *subObject = new QObject(this);
        subObject->setObjectName("subObject");
    }
};

struct MyMember
{
    int subMember1;
    int subMember2;
};

//! [0-0]
struct MyStructure
{
    int count;
    QString name;
//! [0-0]
    MyMember member1;
    MyMember member2;
    MyMember member3;
    MyMember member4;
//! [0-1]
    // ...
};
Q_DECLARE_METATYPE(MyStructure)

// Marshall the MyStructure data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const MyStructure &myStruct)
{
    argument.beginStructure();
    argument << myStruct.count << myStruct.name;
    argument.endStructure();
    return argument;
}

// Retrieve the MyStructure data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, MyStructure &myStruct)
{
    argument.beginStructure();
    argument >> myStruct.count >> myStruct.name;
    argument.endStructure();
    return argument;
}
//! [0-1]

const QDBusArgument &operator<<(const QDBusArgument &argument, const MyMember &/*member*/)
{
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, const MyMember &/*member*/)
{
    return argument;
}

void registerMyStructure()
{
//! [1]
qDBusRegisterMetaType<MyStructure>();
//! [1]
}

void castType()
{
QVariant argument = MyObject::callArgs.at(0);
QDBusVariant dv = qdbus_cast<QDBusVariant>(argument);
//! [2]
MyType item = qdbus_cast<Type>(argument);
//! [2]
}

void argumentItem()
{
//! [3]
MyType item;
argument >> item;
//! [3]
}
namespace QDBusSnippets
{
//! [4]
QDBusArgument &operator<<(QDBusArgument &argument, const MyStructure &myStruct)
{
    argument.beginStructure();
    argument << myStruct.member1 << myStruct.member2;
    argument.endStructure();
    return argument;
}
//! [4]

namespace Alt {
//! [5]
QDBusArgument &operator<<(QDBusArgument &argument, const MyStructure &myStruct)
{
    argument.beginStructure();
    argument << myStruct.member1 << myStruct.member2;

    argument.beginStructure();
    argument << myStruct.member3.subMember1 << myStruct.member3.subMember2;
    argument.endStructure();

    argument << myStruct.member4;
    argument.endStructure();
    return argument;
}
//! [5]
} // namespace

//! [6]
// Append an array of MyElement types
QDBusArgument &operator<<(QDBusArgument &argument, const MyArray &myArray)
{
    argument.beginArray(qMetaTypeId<MyElement>());
    for (const auto &element : myArray)
        argument << element;
    argument.endArray();
    return argument;
}
//! [6]

//! [7]
// Append a dictionary that associates ints to MyValue types
QDBusArgument &operator<<(QDBusArgument &argument, const MyDictionary &myDict)
{
    argument.beginMap(QMetaType::fromType<int>(), QMetaType::fromType<MyValue>());
    MyDictionary::const_iterator i;
    for (i = myDict.cbegin(); i != myDict.cend(); ++i) {
        argument.beginMapEntry();
        argument << i.key() << i.value();
        argument.endMapEntry();
    }
    argument.endMap();
    return argument;
}
//! [7]

//! [8]
const QDBusArgument &operator>>(const QDBusArgument &argument, MyStructure &myStruct)
{
    argument.beginStructure();
    argument >> myStruct.member1 >> myStruct.member2 >> myStruct.member3;
    argument.endStructure();
    return argument;
}
//! [8]

//! [9]
// Extract a MyArray array of MyElement elements
const QDBusArgument &operator>>(const QDBusArgument &argument, MyArray &myArray)
{
    argument.beginArray();
    myArray.clear();

    while (!argument.atEnd()) {
        MyElement element;
        argument >> element;
        myArray.append(element);
    }

    argument.endArray();
    return argument;
}
//! [9]

//! [10]
// Extract a MyDictionary map that associates integers to MyElement items
const QDBusArgument &operator>>(const QDBusArgument &argument, MyDictionary &myDict)
{
    argument.beginMap();
    myDict.clear();

    while (!argument.atEnd()) {
        int key;
        MyElement value;
        argument.beginMapEntry();
        argument >> key >> value;
        argument.endMapEntry();
        myDict.insert(key, value);
    }

    argument.endMap();
    return argument;
}
//! [10]
}
