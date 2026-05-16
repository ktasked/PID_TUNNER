/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/mainwindow.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[34];
    char stringdata0[11];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[20];
    char stringdata5[21];
    char stringdata6[21];
    char stringdata7[28];
    char stringdata8[22];
    char stringdata9[6];
    char stringdata10[18];
    char stringdata11[26];
    char stringdata12[7];
    char stringdata13[18];
    char stringdata14[37];
    char stringdata15[6];
    char stringdata16[42];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 18),  // "on_btnTune_clicked"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 22),  // "on_btnSimulate_clicked"
        QT_MOC_LITERAL(54, 19),  // "on_btnReset_clicked"
        QT_MOC_LITERAL(74, 20),  // "on_btnExport_clicked"
        QT_MOC_LITERAL(95, 20),  // "on_btnImport_clicked"
        QT_MOC_LITERAL(116, 27),  // "on_btnApplySettings_clicked"
        QT_MOC_LITERAL(144, 21),  // "onProcessValueChanged"
        QT_MOC_LITERAL(166, 5),  // "value"
        QT_MOC_LITERAL(172, 17),  // "onSetpointChanged"
        QT_MOC_LITERAL(190, 25),  // "onControllerOutputChanged"
        QT_MOC_LITERAL(216, 6),  // "output"
        QT_MOC_LITERAL(223, 17),  // "onSimulationTimer"
        QT_MOC_LITERAL(241, 36),  // "onMethodComboBox_currentIndex..."
        QT_MOC_LITERAL(278, 5),  // "index"
        QT_MOC_LITERAL(284, 41)   // "onProcessTypeComboBox_current..."
    },
    "MainWindow",
    "on_btnTune_clicked",
    "",
    "on_btnSimulate_clicked",
    "on_btnReset_clicked",
    "on_btnExport_clicked",
    "on_btnImport_clicked",
    "on_btnApplySettings_clicked",
    "onProcessValueChanged",
    "value",
    "onSetpointChanged",
    "onControllerOutputChanged",
    "output",
    "onSimulationTimer",
    "onMethodComboBox_currentIndexChanged",
    "index",
    "onProcessTypeComboBox_currentIndexChanged"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    0,   90,    2, 0x08,    5 /* Private */,
       7,    0,   91,    2, 0x08,    6 /* Private */,
       8,    1,   92,    2, 0x08,    7 /* Private */,
      10,    1,   95,    2, 0x08,    9 /* Private */,
      11,    1,   98,    2, 0x08,   11 /* Private */,
      13,    0,  101,    2, 0x08,   13 /* Private */,
      14,    1,  102,    2, 0x08,   14 /* Private */,
      16,    1,  105,    2, 0x08,   16 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_btnTune_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSimulate_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnReset_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnExport_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnImport_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnApplySettings_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onProcessValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onSetpointChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onControllerOutputChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onSimulationTimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMethodComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onProcessTypeComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btnTune_clicked(); break;
        case 1: _t->on_btnSimulate_clicked(); break;
        case 2: _t->on_btnReset_clicked(); break;
        case 3: _t->on_btnExport_clicked(); break;
        case 4: _t->on_btnImport_clicked(); break;
        case 5: _t->on_btnApplySettings_clicked(); break;
        case 6: _t->onProcessValueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 7: _t->onSetpointChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 8: _t->onControllerOutputChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->onSimulationTimer(); break;
        case 10: _t->onMethodComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->onProcessTypeComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
