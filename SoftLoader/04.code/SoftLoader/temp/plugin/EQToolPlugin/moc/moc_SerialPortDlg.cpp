/****************************************************************************
** Meta object code from reading C++ file 'SerialPortDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../common/serialport/SerialPortDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SerialPortDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialPortDlg_t {
    QByteArrayData data[14];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPortDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPortDlg_t qt_meta_stringdata_SerialPortDlg = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SerialPortDlg"
QT_MOC_LITERAL(1, 14, 14), // "slot_recv_data"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "strData"
QT_MOC_LITERAL(4, 38, 14), // "slot_btn_start"
QT_MOC_LITERAL(5, 53, 13), // "slot_btn_stop"
QT_MOC_LITERAL(6, 67, 13), // "slot_btn_send"
QT_MOC_LITERAL(7, 81, 17), // "slot_btn_send_IIR"
QT_MOC_LITERAL(8, 99, 14), // "slot_btn_clear"
QT_MOC_LITERAL(9, 114, 23), // "slot_recv_radio_clicked"
QT_MOC_LITERAL(10, 138, 8), // "bChecked"
QT_MOC_LITERAL(11, 147, 23), // "slot_send_radio_clicked"
QT_MOC_LITERAL(12, 171, 26), // "slot_checkbox_stateChanged"
QT_MOC_LITERAL(13, 198, 5) // "state"

    },
    "SerialPortDlg\0slot_recv_data\0\0strData\0"
    "slot_btn_start\0slot_btn_stop\0slot_btn_send\0"
    "slot_btn_send_IIR\0slot_btn_clear\0"
    "slot_recv_radio_clicked\0bChecked\0"
    "slot_send_radio_clicked\0"
    "slot_checkbox_stateChanged\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPortDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    0,   62,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x0a /* Public */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    0,   65,    2, 0x0a /* Public */,
       8,    0,   66,    2, 0x0a /* Public */,
       9,    1,   67,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      12,    1,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void SerialPortDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialPortDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_recv_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->slot_btn_start(); break;
        case 2: _t->slot_btn_stop(); break;
        case 3: _t->slot_btn_send(); break;
        case 4: _t->slot_btn_send_IIR(); break;
        case 5: _t->slot_btn_clear(); break;
        case 6: _t->slot_recv_radio_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slot_send_radio_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slot_checkbox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SerialPortDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_SerialPortDlg.data,
    qt_meta_data_SerialPortDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SerialPortDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPortDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPortDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SerialPortDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
