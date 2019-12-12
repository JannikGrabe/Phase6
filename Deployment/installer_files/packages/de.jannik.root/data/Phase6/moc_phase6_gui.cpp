/****************************************************************************
** Meta object code from reading C++ file 'phase6_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Phase6/phase6_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'phase6_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Phase6_GUI_t {
    QByteArrayData data[9];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Phase6_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Phase6_GUI_t qt_meta_stringdata_Phase6_GUI = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Phase6_GUI"
QT_MOC_LITERAL(1, 11, 17), // "on_pb_add_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "on_pb_edit_clicked"
QT_MOC_LITERAL(4, 49, 18), // "on_pb_next_clicked"
QT_MOC_LITERAL(5, 68, 19), // "on_rb_lang1_clicked"
QT_MOC_LITERAL(6, 88, 19), // "on_rb_lang2_clicked"
QT_MOC_LITERAL(7, 108, 26), // "on_le_answer_returnPressed"
QT_MOC_LITERAL(8, 135, 22) // "on_pb_overview_clicked"

    },
    "Phase6_GUI\0on_pb_add_clicked\0\0"
    "on_pb_edit_clicked\0on_pb_next_clicked\0"
    "on_rb_lang1_clicked\0on_rb_lang2_clicked\0"
    "on_le_answer_returnPressed\0"
    "on_pb_overview_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Phase6_GUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Phase6_GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Phase6_GUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pb_add_clicked(); break;
        case 1: _t->on_pb_edit_clicked(); break;
        case 2: _t->on_pb_next_clicked(); break;
        case 3: _t->on_rb_lang1_clicked(); break;
        case 4: _t->on_rb_lang2_clicked(); break;
        case 5: _t->on_le_answer_returnPressed(); break;
        case 6: _t->on_pb_overview_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Phase6_GUI::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Phase6_GUI.data,
    qt_meta_data_Phase6_GUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Phase6_GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Phase6_GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Phase6_GUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Phase6_GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
