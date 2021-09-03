/****************************************************************************
** Meta object code from reading C++ file 'ConfItemWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../ConfItemPlugin/ConfItemWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfItemWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfItemWgt_t {
    QByteArrayData data[13];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfItemWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfItemWgt_t qt_meta_stringdata_ConfItemWgt = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ConfItemWgt"
QT_MOC_LITERAL(1, 12, 18), // "slot_cmb_port_init"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "slot_btn_1"
QT_MOC_LITERAL(4, 43, 10), // "slot_btn_2"
QT_MOC_LITERAL(5, 54, 10), // "slot_btn_3"
QT_MOC_LITERAL(6, 65, 10), // "slot_btn_4"
QT_MOC_LITERAL(7, 76, 10), // "slot_btn_5"
QT_MOC_LITERAL(8, 87, 10), // "slot_btn_6"
QT_MOC_LITERAL(9, 98, 10), // "slot_btn_7"
QT_MOC_LITERAL(10, 109, 10), // "slot_btn_8"
QT_MOC_LITERAL(11, 120, 10), // "slot_btn_9"
QT_MOC_LITERAL(12, 131, 14) // "slot_port_recv"

    },
    "ConfItemWgt\0slot_cmb_port_init\0\0"
    "slot_btn_1\0slot_btn_2\0slot_btn_3\0"
    "slot_btn_4\0slot_btn_5\0slot_btn_6\0"
    "slot_btn_7\0slot_btn_8\0slot_btn_9\0"
    "slot_port_recv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfItemWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConfItemWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfItemWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_cmb_port_init(); break;
        case 1: _t->slot_btn_1(); break;
        case 2: _t->slot_btn_2(); break;
        case 3: _t->slot_btn_3(); break;
        case 4: _t->slot_btn_4(); break;
        case 5: _t->slot_btn_5(); break;
        case 6: _t->slot_btn_6(); break;
        case 7: _t->slot_btn_7(); break;
        case 8: _t->slot_btn_8(); break;
        case 9: _t->slot_btn_9(); break;
        case 10: _t->slot_port_recv(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ConfItemWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ConfItemWgt.data,
    qt_meta_data_ConfItemWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfItemWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfItemWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfItemWgt.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ConfItemWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
