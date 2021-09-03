/****************************************************************************
** Meta object code from reading C++ file 'SerialThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SerialThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SerialThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialThread_t {
    QByteArrayData data[17];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialThread_t qt_meta_stringdata_SerialThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SerialThread"
QT_MOC_LITERAL(1, 13, 10), // "sig_status"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "BURN_STATE"
QT_MOC_LITERAL(4, 36, 6), // "nState"
QT_MOC_LITERAL(5, 43, 4), // "nVal"
QT_MOC_LITERAL(6, 48, 7), // "sig_log"
QT_MOC_LITERAL(7, 56, 6), // "strLog"
QT_MOC_LITERAL(8, 63, 10), // "thread_sig"
QT_MOC_LITERAL(9, 74, 9), // "run_erase"
QT_MOC_LITERAL(10, 84, 10), // "next_erase"
QT_MOC_LITERAL(11, 95, 10), // "next_write"
QT_MOC_LITERAL(12, 106, 14), // "slot_init_port"
QT_MOC_LITERAL(13, 121, 10), // "slot_start"
QT_MOC_LITERAL(14, 132, 16), // "slot_handle_data"
QT_MOC_LITERAL(15, 149, 15), // "slot_write_data"
QT_MOC_LITERAL(16, 165, 13) // "erase_process"

    },
    "SerialThread\0sig_status\0\0BURN_STATE\0"
    "nState\0nVal\0sig_log\0strLog\0thread_sig\0"
    "run_erase\0next_erase\0next_write\0"
    "slot_init_port\0slot_start\0slot_handle_data\0"
    "slot_write_data\0erase_process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       1,    1,   79,    2, 0x26 /* Public | MethodCloned */,
       6,    1,   82,    2, 0x06 /* Public */,
       8,    0,   85,    2, 0x06 /* Public */,
       9,    0,   86,    2, 0x06 /* Public */,
      10,    0,   87,    2, 0x06 /* Public */,
      11,    0,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,
      16,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Float,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SerialThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_status((*reinterpret_cast< BURN_STATE(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->sig_status((*reinterpret_cast< BURN_STATE(*)>(_a[1]))); break;
        case 2: _t->sig_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->thread_sig(); break;
        case 4: _t->run_erase(); break;
        case 5: _t->next_erase(); break;
        case 6: _t->next_write(); break;
        case 7: _t->slot_init_port(); break;
        case 8: _t->slot_start(); break;
        case 9: _t->slot_handle_data(); break;
        case 10: _t->slot_write_data(); break;
        case 11: _t->erase_process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialThread::*)(BURN_STATE , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::sig_status)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::sig_log)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::thread_sig)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::run_erase)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::next_erase)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SerialThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialThread::next_write)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SerialThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SerialThread.data,
    qt_meta_data_SerialThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SerialThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SerialThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SerialThread::sig_status(BURN_STATE _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void SerialThread::sig_log(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SerialThread::thread_sig()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SerialThread::run_erase()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SerialThread::next_erase()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SerialThread::next_write()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
