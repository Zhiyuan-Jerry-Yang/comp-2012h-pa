/****************************************************************************
** Meta object code from reading C++ file 'wordleround.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../PA7/app/wordleround.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wordleround.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WordleRound_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WordleRound_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WordleRound_t qt_meta_stringdata_WordleRound = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WordleRound"
QT_MOC_LITERAL(1, 12, 11), // "invalidWord"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "invalidHardWord"
QT_MOC_LITERAL(4, 41, 8), // "roundWin"
QT_MOC_LITERAL(5, 50, 9), // "roundLose"
QT_MOC_LITERAL(6, 60, 19), // "updateKeyboardColor"
QT_MOC_LITERAL(7, 80, 3), // "key"
QT_MOC_LITERAL(8, 84, 5), // "color"
QT_MOC_LITERAL(9, 90, 18) // "resetKeyboardColor"

    },
    "WordleRound\0invalidWord\0\0invalidHardWord\0"
    "roundWin\0roundLose\0updateKeyboardColor\0"
    "key\0color\0resetKeyboardColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WordleRound[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    2,   48,    2, 0x06 /* Public */,
       9,    0,   53,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QChar, QMetaType::QColor,    7,    8,
    QMetaType::Void,

       0        // eod
};

void WordleRound::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WordleRound *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->invalidWord(); break;
        case 1: _t->invalidHardWord(); break;
        case 2: _t->roundWin(); break;
        case 3: _t->roundLose(); break;
        case 4: _t->updateKeyboardColor((*reinterpret_cast< const QChar(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 5: _t->resetKeyboardColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WordleRound::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordleRound::invalidWord)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WordleRound::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordleRound::invalidHardWord)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WordleRound::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordleRound::roundWin)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WordleRound::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordleRound::roundLose)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WordleRound::*)(const QChar & , const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordleRound::updateKeyboardColor)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WordleRound::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordleRound::resetKeyboardColor)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WordleRound::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WordleRound.data,
    qt_meta_data_WordleRound,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WordleRound::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WordleRound::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WordleRound.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WordleRound::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WordleRound::invalidWord()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WordleRound::invalidHardWord()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WordleRound::roundWin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WordleRound::roundLose()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WordleRound::updateKeyboardColor(const QChar & _t1, const QColor & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WordleRound::resetKeyboardColor()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
