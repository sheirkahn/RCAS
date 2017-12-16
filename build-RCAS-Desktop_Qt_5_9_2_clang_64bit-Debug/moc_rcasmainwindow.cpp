/****************************************************************************
** Meta object code from reading C++ file 'rcasmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../RCAS/rcasmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rcasmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RCASMainWindow_t {
    QByteArrayData data[7];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RCASMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RCASMainWindow_t qt_meta_stringdata_RCASMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RCASMainWindow"
QT_MOC_LITERAL(1, 15, 7), // "on_quit"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 33), // "on_RCASMainWindow_iconSizeCha..."
QT_MOC_LITERAL(4, 58, 8), // "iconSize"
QT_MOC_LITERAL(5, 67, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(6, 91, 21) // "on_pushButton_clicked"

    },
    "RCASMainWindow\0on_quit\0\0"
    "on_RCASMainWindow_iconSizeChanged\0"
    "iconSize\0on_pushButton_2_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RCASMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QSize,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RCASMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RCASMainWindow *_t = static_cast<RCASMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->on_quit();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->on_RCASMainWindow_iconSizeChanged((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject RCASMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RCASMainWindow.data,
      qt_meta_data_RCASMainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RCASMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RCASMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RCASMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RCASMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
