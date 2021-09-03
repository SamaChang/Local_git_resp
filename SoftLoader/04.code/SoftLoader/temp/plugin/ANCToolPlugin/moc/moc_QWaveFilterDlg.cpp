/****************************************************************************
** Meta object code from reading C++ file 'QWaveFilterDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../ANCToolPlugin/QWaveFilterDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QWaveFilterDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QWaveFilterDlg_t {
    QByteArrayData data[14];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QWaveFilterDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QWaveFilterDlg_t qt_meta_stringdata_QWaveFilterDlg = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QWaveFilterDlg"
QT_MOC_LITERAL(1, 15, 8), // "sig_conf"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "nType"
QT_MOC_LITERAL(4, 31, 7), // "nSerial"
QT_MOC_LITERAL(5, 39, 7), // "strName"
QT_MOC_LITERAL(6, 47, 28), // "slot_cmb_currentIndexChanged"
QT_MOC_LITERAL(7, 76, 5), // "index"
QT_MOC_LITERAL(8, 82, 13), // "slot_btn_show"
QT_MOC_LITERAL(9, 96, 18), // "slot_btn_save_conf"
QT_MOC_LITERAL(10, 115, 20), // "slot_btn_data_saveas"
QT_MOC_LITERAL(11, 136, 17), // "slot_btn_load_iir"
QT_MOC_LITERAL(12, 154, 15), // "slot_btn_set_db"
QT_MOC_LITERAL(13, 170, 15) // "slot_btn_set_xx"

    },
    "QWaveFilterDlg\0sig_conf\0\0nType\0nSerial\0"
    "strName\0slot_cmb_currentIndexChanged\0"
    "index\0slot_btn_show\0slot_btn_save_conf\0"
    "slot_btn_data_saveas\0slot_btn_load_iir\0"
    "slot_btn_set_db\0slot_btn_set_xx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWaveFilterDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   61,    2, 0x0a /* Public */,
       8,    0,   64,    2, 0x0a /* Public */,
       9,    0,   65,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QWaveFilterDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QWaveFilterDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_conf((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->slot_cmb_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_btn_show(); break;
        case 3: _t->slot_btn_save_conf(); break;
        case 4: _t->slot_btn_data_saveas(); break;
        case 5: _t->slot_btn_load_iir(); break;
        case 6: _t->slot_btn_set_db(); break;
        case 7: _t->slot_btn_set_xx(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QWaveFilterDlg::*)(int , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWaveFilterDlg::sig_conf)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QWaveFilterDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_QWaveFilterDlg.data,
    qt_meta_data_QWaveFilterDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QWaveFilterDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWaveFilterDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QWaveFilterDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int QWaveFilterDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QWaveFilterDlg::sig_conf(int _t1, int _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
