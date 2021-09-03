/****************************************************************************
** Meta object code from reading C++ file 'RealTimeEngine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../ANCToolPlugin/RealTimeEngine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RealTimeEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RealTimeEngine_t {
    QByteArrayData data[21];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RealTimeEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RealTimeEngine_t qt_meta_stringdata_RealTimeEngine = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RealTimeEngine"
QT_MOC_LITERAL(1, 15, 12), // "stateChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QAudio::Mode"
QT_MOC_LITERAL(4, 42, 4), // "mode"
QT_MOC_LITERAL(5, 47, 13), // "QAudio::State"
QT_MOC_LITERAL(6, 61, 5), // "state"
QT_MOC_LITERAL(7, 67, 13), // "formatChanged"
QT_MOC_LITERAL(8, 81, 12), // "QAudioFormat"
QT_MOC_LITERAL(9, 94, 6), // "format"
QT_MOC_LITERAL(10, 101, 15), // "spectrumChanged"
QT_MOC_LITERAL(11, 117, 8), // "position"
QT_MOC_LITERAL(12, 126, 6), // "length"
QT_MOC_LITERAL(13, 133, 17), // "FrequencySpectrum"
QT_MOC_LITERAL(14, 151, 8), // "spectrum"
QT_MOC_LITERAL(15, 160, 14), // "startRecording"
QT_MOC_LITERAL(16, 175, 13), // "startPlayback"
QT_MOC_LITERAL(17, 189, 7), // "suspend"
QT_MOC_LITERAL(18, 197, 11), // "audioNotify"
QT_MOC_LITERAL(19, 209, 17), // "audioStateChanged"
QT_MOC_LITERAL(20, 227, 14) // "audioDataReady"

    },
    "RealTimeEngine\0stateChanged\0\0QAudio::Mode\0"
    "mode\0QAudio::State\0state\0formatChanged\0"
    "QAudioFormat\0format\0spectrumChanged\0"
    "position\0length\0FrequencySpectrum\0"
    "spectrum\0startRecording\0startPlayback\0"
    "suspend\0audioNotify\0audioStateChanged\0"
    "audioDataReady"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealTimeEngine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       7,    1,   69,    2, 0x06 /* Public */,
      10,    3,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   79,    2, 0x0a /* Public */,
      16,    0,   80,    2, 0x0a /* Public */,
      17,    0,   81,    2, 0x0a /* Public */,
      18,    0,   82,    2, 0x08 /* Private */,
      19,    1,   83,    2, 0x08 /* Private */,
      20,    0,   86,    2, 0x08 /* Private */,
      10,    1,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 13,   11,   12,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void RealTimeEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RealTimeEngine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< QAudio::Mode(*)>(_a[1])),(*reinterpret_cast< QAudio::State(*)>(_a[2]))); break;
        case 1: _t->formatChanged((*reinterpret_cast< const QAudioFormat(*)>(_a[1]))); break;
        case 2: _t->spectrumChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const FrequencySpectrum(*)>(_a[3]))); break;
        case 3: _t->startRecording(); break;
        case 4: _t->startPlayback(); break;
        case 5: _t->suspend(); break;
        case 6: _t->audioNotify(); break;
        case 7: _t->audioStateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        case 8: _t->audioDataReady(); break;
        case 9: _t->spectrumChanged((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::Mode >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudioFormat >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RealTimeEngine::*)(QAudio::Mode , QAudio::State );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RealTimeEngine::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RealTimeEngine::*)(const QAudioFormat & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RealTimeEngine::formatChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RealTimeEngine::*)(qint64 , qint64 , const FrequencySpectrum & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RealTimeEngine::spectrumChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RealTimeEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RealTimeEngine.data,
    qt_meta_data_RealTimeEngine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RealTimeEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RealTimeEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RealTimeEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RealTimeEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void RealTimeEngine::stateChanged(QAudio::Mode _t1, QAudio::State _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RealTimeEngine::formatChanged(const QAudioFormat & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RealTimeEngine::spectrumChanged(qint64 _t1, qint64 _t2, const FrequencySpectrum & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
