/****************************************************************************
** Meta object code from reading C++ file 'EQToolPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../EQToolPlugin/EQToolPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EQToolPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EQToolPlugin_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EQToolPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EQToolPlugin_t qt_meta_stringdata_EQToolPlugin = {
    {
QT_MOC_LITERAL(0, 0, 12) // "EQToolPlugin"

    },
    "EQToolPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EQToolPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void EQToolPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject EQToolPlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_EQToolPlugin.data,
    qt_meta_data_EQToolPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EQToolPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EQToolPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EQToolPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "MyInterface"))
        return static_cast< MyInterface*>(this);
    if (!strcmp(_clname, "TSingmicro.PlatformOne.HC.Plugin"))
        return static_cast< MyInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int EQToolPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x31,  'T',  'S',  'i',  'n',  'g', 
    'm',  'i',  'c',  'r',  'o',  '.',  'P',  'l', 
    'a',  't',  'f',  'o',  'r',  'm',  'O',  'n', 
    'e',  '.',  'H',  'C',  '.',  'P',  'l',  'u', 
    'g',  'i',  'n',  '.',  'E',  'Q',  'T',  'o', 
    'o',  'l',  '.',  'I',  'n',  't',  'e',  'r', 
    'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x6c,  'E',  'Q',  'T',  'o',  'o',  'l', 
    'P',  'l',  'u',  'g',  'i',  'n', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(EQToolPlugin, EQToolPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
