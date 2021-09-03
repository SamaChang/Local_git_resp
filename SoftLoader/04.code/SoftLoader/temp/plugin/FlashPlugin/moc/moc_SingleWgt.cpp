/****************************************************************************
** Meta object code from reading C++ file 'SingleWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../FlashPlugin/SingleWgt.h"
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
    QByteArrayData data[12];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleWgt_t qt_meta_stringdata_SingleWgt = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SingleWgt"
QT_MOC_LITERAL(1, 10, 7), // "sig_log"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "strLog"
QT_MOC_LITERAL(4, 26, 13), // "sig_loop_quit"
QT_MOC_LITERAL(5, 40, 8), // "sig_init"
QT_MOC_LITERAL(6, 49, 9), // "sig_start"
QT_MOC_LITERAL(7, 59, 17), // "sig_burn_finished"
QT_MOC_LITERAL(8, 77, 23), // "slot_thread_port_status"
QT_MOC_LITERAL(9, 101, 10), // "BURN_STATE"
QT_MOC_LITERAL(10, 112, 7), // "nStatus"
QT_MOC_LITERAL(11, 120, 11) // "nValProcess"

    },
    "SingleWgt\0sig_log\0\0strLog\0sig_loop_quit\0"
    "sig_init\0sig_start\0sig_burn_finished\0"
    "slot_thread_port_status\0BURN_STATE\0"
    "nStatus\0nValProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,
       5,    0,   53,    2, 0x06 /* Public */,
       6,    0,   54,    2, 0x06 /* Public */,
       7,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   56,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9, QMetaType::Float,   10,   11,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void SingleWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_loop_quit(); break;
        case 2: _t->sig_init(); break;
        case 3: _t->sig_start(); break;
        case 4: _t->sig_burn_finished(); break;
        case 5: _t->slot_thread_port_status((*reinterpret_cast< BURN_STATE(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->slot_thread_port_status((*reinterpret_cast< BURN_STATE(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SingleWgt::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_log)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_loop_quit)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_init)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_start)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SingleWgt::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleWgt::sig_burn_finished)) {
                *result = 4;
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SingleWgt::sig_log(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SingleWgt::sig_loop_quit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SingleWgt::sig_init()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SingleWgt::sig_start()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SingleWgt::sig_burn_finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
