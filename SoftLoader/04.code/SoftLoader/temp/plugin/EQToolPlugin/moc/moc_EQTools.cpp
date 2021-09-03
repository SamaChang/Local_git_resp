/****************************************************************************
** Meta object code from reading C++ file 'EQTools.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../EQToolPlugin/EQTools.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EQTools.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EQTools_t {
    QByteArrayData data[20];
    char stringdata0[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EQTools_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EQTools_t qt_meta_stringdata_EQTools = {
    {
QT_MOC_LITERAL(0, 0, 7), // "EQTools"
QT_MOC_LITERAL(1, 8, 23), // "slot_voice_valueChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "nTotal_Gain"
QT_MOC_LITERAL(4, 45, 24), // "slot_slider_valueChanged"
QT_MOC_LITERAL(5, 70, 4), // "nVal"
QT_MOC_LITERAL(6, 75, 25), // "slot_spinbox_valueChanged"
QT_MOC_LITERAL(7, 101, 4), // "dVal"
QT_MOC_LITERAL(8, 106, 22), // "slot_boost_textChanged"
QT_MOC_LITERAL(9, 129, 4), // "text"
QT_MOC_LITERAL(10, 134, 18), // "slot_Q_textChanged"
QT_MOC_LITERAL(11, 153, 29), // "slot_chart_boost_valueChanged"
QT_MOC_LITERAL(12, 183, 6), // "nIndex"
QT_MOC_LITERAL(13, 190, 13), // "slot_btn_open"
QT_MOC_LITERAL(14, 204, 13), // "slot_btn_save"
QT_MOC_LITERAL(15, 218, 17), // "slot_btn_link_dev"
QT_MOC_LITERAL(16, 236, 23), // "slot_btn_write_hardware"
QT_MOC_LITERAL(17, 260, 23), // "slot_btn_clear_log_info"
QT_MOC_LITERAL(18, 284, 14), // "slot_recv_data"
QT_MOC_LITERAL(19, 299, 7) // "strData"

    },
    "EQTools\0slot_voice_valueChanged\0\0"
    "nTotal_Gain\0slot_slider_valueChanged\0"
    "nVal\0slot_spinbox_valueChanged\0dVal\0"
    "slot_boost_textChanged\0text\0"
    "slot_Q_textChanged\0slot_chart_boost_valueChanged\0"
    "nIndex\0slot_btn_open\0slot_btn_save\0"
    "slot_btn_link_dev\0slot_btn_write_hardware\0"
    "slot_btn_clear_log_info\0slot_recv_data\0"
    "strData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EQTools[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       4,    1,   77,    2, 0x0a /* Public */,
       6,    1,   80,    2, 0x0a /* Public */,
       8,    1,   83,    2, 0x0a /* Public */,
      10,    1,   86,    2, 0x0a /* Public */,
      11,    2,   89,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x0a /* Public */,
      14,    0,   95,    2, 0x0a /* Public */,
      15,    0,   96,    2, 0x0a /* Public */,
      16,    0,   97,    2, 0x0a /* Public */,
      17,    0,   98,    2, 0x0a /* Public */,
      18,    1,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   19,

       0        // eod
};

void EQTools::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EQTools *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_voice_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_spinbox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->slot_boost_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slot_Q_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slot_chart_boost_valueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slot_btn_open(); break;
        case 7: _t->slot_btn_save(); break;
        case 8: _t->slot_btn_link_dev(); break;
        case 9: _t->slot_btn_write_hardware(); break;
        case 10: _t->slot_btn_clear_log_info(); break;
        case 11: _t->slot_recv_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EQTools::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EQTools.data,
    qt_meta_data_EQTools,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EQTools::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EQTools::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EQTools.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EQTools::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
