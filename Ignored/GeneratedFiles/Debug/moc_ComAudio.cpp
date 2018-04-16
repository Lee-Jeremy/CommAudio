/****************************************************************************
** Meta object code from reading C++ file 'ComAudio.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ComAudio.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComAudio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComAudio_t {
    QByteArrayData data[19];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComAudio_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComAudio_t qt_meta_stringdata_ComAudio = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ComAudio"
QT_MOC_LITERAL(1, 9, 6), // "setDir"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 9), // "selectDir"
QT_MOC_LITERAL(4, 27, 10), // "selectFile"
QT_MOC_LITERAL(5, 38, 9), // "playAudio"
QT_MOC_LITERAL(6, 48, 9), // "setVolume"
QT_MOC_LITERAL(7, 58, 15), // "metaDataChanged"
QT_MOC_LITERAL(8, 74, 7), // "initTab"
QT_MOC_LITERAL(9, 82, 10), // "Task::Type"
QT_MOC_LITERAL(10, 93, 4), // "task"
QT_MOC_LITERAL(11, 98, 8), // "closeTab"
QT_MOC_LITERAL(12, 107, 8), // "QWidget*"
QT_MOC_LITERAL(13, 116, 3), // "tab"
QT_MOC_LITERAL(14, 120, 13), // "initTabFileTx"
QT_MOC_LITERAL(15, 134, 11), // "getFileList"
QT_MOC_LITERAL(16, 146, 18), // "initTabAudioStream"
QT_MOC_LITERAL(17, 165, 16), // "initTabAudioChat"
QT_MOC_LITERAL(18, 182, 16) // "initTabMulticast"

    },
    "ComAudio\0setDir\0\0selectDir\0selectFile\0"
    "playAudio\0setVolume\0metaDataChanged\0"
    "initTab\0Task::Type\0task\0closeTab\0"
    "QWidget*\0tab\0initTabFileTx\0getFileList\0"
    "initTabAudioStream\0initTabAudioChat\0"
    "initTabMulticast"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComAudio[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
      11,    1,   88,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,
      16,    0,   93,    2, 0x0a /* Public */,
      17,    0,   94,    2, 0x0a /* Public */,
      18,    0,   95,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ComAudio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComAudio *_t = static_cast<ComAudio *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setDir(); break;
        case 1: _t->selectDir(); break;
        case 2: _t->selectFile(); break;
        case 3: _t->playAudio(); break;
        case 4: _t->setVolume(); break;
        case 5: _t->metaDataChanged(); break;
        case 6: _t->initTab((*reinterpret_cast< Task::Type(*)>(_a[1]))); break;
        case 7: _t->closeTab((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 8: _t->initTabFileTx(); break;
        case 9: { QString _r = _t->getFileList();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->initTabAudioStream(); break;
        case 11: _t->initTabAudioChat(); break;
        case 12: _t->initTabMulticast(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ComAudio::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ComAudio.data,
      qt_meta_data_ComAudio,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ComAudio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComAudio::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComAudio.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ComAudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
