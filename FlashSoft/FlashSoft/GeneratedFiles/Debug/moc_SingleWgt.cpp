/****************************************************************************
** Meta object code from reading C++ file 'SingleWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SingleWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SingleWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SingleWgt_t {
    QByteArrayData data[10];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleWgt_t qt_meta_stringdata_SingleWgt = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SingleWgt"
QT_MOC_LITERAL(1, 10, 13), // "sig_loop_quit"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "sig_init"
QT_MOC_LITERAL(4, 34, 9), // "sig_start"
QT_MOC_LITERAL(5, 44, 17), // "sig_burn_finished"
QT_MOC_LITERAL(6, 62, 23), // "slot_thread_port_status"
QT_MOC_LITERAL(7, 86, 10), // "BURN_STATE"
QT_MOC_LITERAL(8, 97, 7), // "nStatus"
QT_MOC_LITERAL(9, 105, 11) // "nValProcess"

    },
    "SingleWgt\0sig_loop_quit\0\0sig_init\0"
    "sig_start\0sig_burn_finished\0"
    "slot_thread_port_status\0BURN_STATE\0"
    "nStatus\0nValProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   48,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, QMetaType::Float,    8,    9,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void SingleWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_loop_quit(); break;
        case 1: _t->sig_init(); break;
        case 2: _t->sig_start(); break;
        case 3: _t->sig_burn_finished(); break;
        case 4: _t->slot_thread_port_status((*reinterpret_cast< BURN_STATE(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->slot_thread_port_status((*reinterpret_cast< BURN_STATE(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_loop_quit)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_init)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_start)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_burn_finished)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SingleWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SingleWgt.data,
    qt_meta_data_SingleWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SingleWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SingleWgt.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SingleWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SingleWgt::sig_loop_quit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SingleWgt::sig_init()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SingleWgt::sig_start()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SingleWgt::sig_burn_finished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
