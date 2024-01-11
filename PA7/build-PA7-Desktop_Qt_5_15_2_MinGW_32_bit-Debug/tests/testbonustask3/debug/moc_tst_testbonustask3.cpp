/****************************************************************************
** Meta object code from reading C++ file 'tst_testbonustask3.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../PA7/tests/testbonustask3/tst_testbonustask3.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_testbonustask3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestBonusTask3_t {
    QByteArrayData data[7];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestBonusTask3_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestBonusTask3_t qt_meta_stringdata_TestBonusTask3 = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TestBonusTask3"
QT_MOC_LITERAL(1, 15, 25), // "testTimedRoundWindowBasic"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 31), // "testTimedRoundWindowInvalidWord"
QT_MOC_LITERAL(4, 74, 28), // "testTimedRoundWindowRoundWin"
QT_MOC_LITERAL(5, 103, 28), // "testTimedRoundWindowSkipWord"
QT_MOC_LITERAL(6, 132, 19) // "testTimedMainWindow"

    },
    "TestBonusTask3\0testTimedRoundWindowBasic\0"
    "\0testTimedRoundWindowInvalidWord\0"
    "testTimedRoundWindowRoundWin\0"
    "testTimedRoundWindowSkipWord\0"
    "testTimedMainWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestBonusTask3[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TestBonusTask3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestBonusTask3 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testTimedRoundWindowBasic(); break;
        case 1: _t->testTimedRoundWindowInvalidWord(); break;
        case 2: _t->testTimedRoundWindowRoundWin(); break;
        case 3: _t->testTimedRoundWindowSkipWord(); break;
        case 4: _t->testTimedMainWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TestBonusTask3::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TestBonusTask3.data,
    qt_meta_data_TestBonusTask3,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestBonusTask3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestBonusTask3::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestBonusTask3.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TestBonusTask3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
