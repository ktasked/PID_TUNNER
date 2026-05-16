/****************************************************************************
** Meta object code from reading C++ file 'pidcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/pidcontroller.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pidcontroller.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_PIDController_t {
    uint offsetsAndSizes[36];
    char stringdata0[14];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[3];
    char stringdata4[10];
    char stringdata5[3];
    char stringdata6[10];
    char stringdata7[3];
    char stringdata8[16];
    char stringdata9[9];
    char stringdata10[14];
    char stringdata11[7];
    char stringdata12[12];
    char stringdata13[9];
    char stringdata14[21];
    char stringdata15[6];
    char stringdata16[19];
    char stringdata17[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PIDController_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_PIDController_t qt_meta_stringdata_PIDController = {
    {
        QT_MOC_LITERAL(0, 13),  // "PIDController"
        QT_MOC_LITERAL(14, 9),  // "kpChanged"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 2),  // "kp"
        QT_MOC_LITERAL(28, 9),  // "kiChanged"
        QT_MOC_LITERAL(38, 2),  // "ki"
        QT_MOC_LITERAL(41, 9),  // "kdChanged"
        QT_MOC_LITERAL(51, 2),  // "kd"
        QT_MOC_LITERAL(54, 15),  // "setpointChanged"
        QT_MOC_LITERAL(70, 8),  // "setpoint"
        QT_MOC_LITERAL(79, 13),  // "outputChanged"
        QT_MOC_LITERAL(93, 6),  // "output"
        QT_MOC_LITERAL(100, 11),  // "modeChanged"
        QT_MOC_LITERAL(112, 8),  // "autoMode"
        QT_MOC_LITERAL(121, 20),  // "computationCompleted"
        QT_MOC_LITERAL(142, 5),  // "error"
        QT_MOC_LITERAL(148, 18),  // "saturationOccurred"
        QT_MOC_LITERAL(167, 9)   // "saturated"
    },
    "PIDController",
    "kpChanged",
    "",
    "kp",
    "kiChanged",
    "ki",
    "kdChanged",
    "kd",
    "setpointChanged",
    "setpoint",
    "outputChanged",
    "output",
    "modeChanged",
    "autoMode",
    "computationCompleted",
    "error",
    "saturationOccurred",
    "saturated"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_PIDController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       6,   88, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    7 /* Public */,
       4,    1,   65,    2, 0x06,    9 /* Public */,
       6,    1,   68,    2, 0x06,   11 /* Public */,
       8,    1,   71,    2, 0x06,   13 /* Public */,
      10,    1,   74,    2, 0x06,   15 /* Public */,
      12,    1,   77,    2, 0x06,   17 /* Public */,
      14,    2,   80,    2, 0x06,   19 /* Public */,
      16,    1,   85,    2, 0x06,   22 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   11,   15,
    QMetaType::Void, QMetaType::Bool,   17,

 // properties: name, type, flags
       3, QMetaType::Double, 0x00015103, uint(0), 0,
       5, QMetaType::Double, 0x00015103, uint(1), 0,
       7, QMetaType::Double, 0x00015103, uint(2), 0,
       9, QMetaType::Double, 0x00015103, uint(3), 0,
      11, QMetaType::Double, 0x00015001, uint(4), 0,
      13, QMetaType::Bool, 0x00015103, uint(5), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject PIDController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PIDController.offsetsAndSizes,
    qt_meta_data_PIDController,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_PIDController_t,
        // property 'kp'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'ki'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'kd'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'setpoint'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'output'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'autoMode'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PIDController, std::true_type>,
        // method 'kpChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'kiChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'kdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'setpointChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'outputChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'modeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'computationCompleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'saturationOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void PIDController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PIDController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->kpChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->kiChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->kdChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->setpointChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->outputChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->computationCompleted((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 7: _t->saturationOccurred((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PIDController::*)(double );
            if (_t _q_method = &PIDController::kpChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(double );
            if (_t _q_method = &PIDController::kiChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(double );
            if (_t _q_method = &PIDController::kdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(double );
            if (_t _q_method = &PIDController::setpointChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(double );
            if (_t _q_method = &PIDController::outputChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(bool );
            if (_t _q_method = &PIDController::modeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(double , double );
            if (_t _q_method = &PIDController::computationCompleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PIDController::*)(bool );
            if (_t _q_method = &PIDController::saturationOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PIDController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->getKp(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->getKi(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->getKd(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->getSetpoint(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->getOutput(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isAutoMode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PIDController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setKp(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setKi(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setKd(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setSetpoint(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setAutoMode(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *PIDController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PIDController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PIDController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PIDController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PIDController::kpChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PIDController::kiChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PIDController::kdChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PIDController::setpointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PIDController::outputChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PIDController::modeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PIDController::computationCompleted(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PIDController::saturationOccurred(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
