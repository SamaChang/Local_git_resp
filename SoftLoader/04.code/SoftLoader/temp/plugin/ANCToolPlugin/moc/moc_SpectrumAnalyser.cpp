/****************************************************************************
** Meta object code from reading C++ file 'SpectrumAnalyser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../ANCToolPlugin/SpectrumAnalyser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpectrumAnalyser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpectrumAnalyserThread_t {
    QByteArrayData data[16];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpectrumAnalyserThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpectrumAnalyserThread_t qt_meta_stringdata_SpectrumAnalyserThread = {
    {
QT_MOC_LITERAL(0, 0, 22), // "SpectrumAnalyserThread"
QT_MOC_LITERAL(1, 23, 20), // "calculattionComplete"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 17), // "FrequencySpectrum"
QT_MOC_LITERAL(4, 63, 8), // "spectrum"
QT_MOC_LITERAL(5, 72, 17), // "setWindowFunction"
QT_MOC_LITERAL(6, 90, 14), // "WindowFunction"
QT_MOC_LITERAL(7, 105, 4), // "type"
QT_MOC_LITERAL(8, 110, 24), // "calculateSpectrum_single"
QT_MOC_LITERAL(9, 135, 20), // "QVector<COMPLEX_OUT>"
QT_MOC_LITERAL(10, 156, 10), // "input_left"
QT_MOC_LITERAL(11, 167, 14), // "inputFrequency"
QT_MOC_LITERAL(12, 182, 14), // "bytesPerSample"
QT_MOC_LITERAL(13, 197, 9), // "nChannels"
QT_MOC_LITERAL(14, 207, 23), // "calculateSpectrum_music"
QT_MOC_LITERAL(15, 231, 11) // "input_right"

    },
    "SpectrumAnalyserThread\0calculattionComplete\0"
    "\0FrequencySpectrum\0spectrum\0"
    "setWindowFunction\0WindowFunction\0type\0"
    "calculateSpectrum_single\0QVector<COMPLEX_OUT>\0"
    "input_left\0inputFrequency\0bytesPerSample\0"
    "nChannels\0calculateSpectrum_music\0"
    "input_right"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpectrumAnalyserThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x0a /* Public */,
       8,    4,   40,    2, 0x0a /* Public */,
      14,    5,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   15,   11,   12,   13,

       0        // eod
};

void SpectrumAnalyserThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpectrumAnalyserThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->calculattionComplete((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        case 1: _t->setWindowFunction((*reinterpret_cast< WindowFunction(*)>(_a[1]))); break;
        case 2: _t->calculateSpectrum_single((*reinterpret_cast< const QVector<COMPLEX_OUT>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->calculateSpectrum_music((*reinterpret_cast< const QVector<COMPLEX_OUT>(*)>(_a[1])),(*reinterpret_cast< const QVector<COMPLEX_OUT>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SpectrumAnalyserThread::*)(const FrequencySpectrum & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpectrumAnalyserThread::calculattionComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpectrumAnalyserThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SpectrumAnalyserThread.data,
    qt_meta_data_SpectrumAnalyserThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpectrumAnalyserThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpectrumAnalyserThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpectrumAnalyserThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SpectrumAnalyserThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SpectrumAnalyserThread::calculattionComplete(const FrequencySpectrum & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SpectrumAnalyser_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpectrumAnalyser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpectrumAnalyser_t qt_meta_stringdata_SpectrumAnalyser = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SpectrumAnalyser"
QT_MOC_LITERAL(1, 17, 15), // "spectrumChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "FrequencySpectrum"
QT_MOC_LITERAL(4, 52, 8), // "spectrum"
QT_MOC_LITERAL(5, 61, 19) // "calculationComplete"

    },
    "SpectrumAnalyser\0spectrumChanged\0\0"
    "FrequencySpectrum\0spectrum\0"
    "calculationComplete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpectrumAnalyser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SpectrumAnalyser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpectrumAnalyser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->spectrumChanged((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        case 1: _t->calculationComplete((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SpectrumAnalyser::*)(const FrequencySpectrum & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpectrumAnalyser::spectrumChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpectrumAnalyser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SpectrumAnalyser.data,
    qt_meta_data_SpectrumAnalyser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpectrumAnalyser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpectrumAnalyser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpectrumAnalyser.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SpectrumAnalyser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SpectrumAnalyser::spectrumChanged(const FrequencySpectrum & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
