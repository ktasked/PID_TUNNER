/****************************************************************************
** Meta object code from reading C++ file 'processmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/processmodel.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processmodel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_ProcessModel_t {
    uint offsetsAndSizes[38];
    char stringdata0[13];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[20];
    char stringdata5[6];
    char stringdata6[19];
    char stringdata7[12];
    char stringdata8[5];
    char stringdata9[20];
    char stringdata10[16];
    char stringdata11[7];
    char stringdata12[18];
    char stringdata13[10];
    char stringdata14[17];
    char stringdata15[7];
    char stringdata16[13];
    char stringdata17[13];
    char stringdata18[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ProcessModel_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ProcessModel_t qt_meta_stringdata_ProcessModel = {
    {
        QT_MOC_LITERAL(0, 12),  // "ProcessModel"
        QT_MOC_LITERAL(13, 19),  // "processValueChanged"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 5),  // "value"
        QT_MOC_LITERAL(40, 19),  // "controlInputChanged"
        QT_MOC_LITERAL(60, 5),  // "input"
        QT_MOC_LITERAL(66, 18),  // "processTypeChanged"
        QT_MOC_LITERAL(85, 11),  // "ProcessType"
        QT_MOC_LITERAL(97, 4),  // "type"
        QT_MOC_LITERAL(102, 19),  // "parameterIdentified"
        QT_MOC_LITERAL(122, 15),  // "ModelParameters"
        QT_MOC_LITERAL(138, 6),  // "params"
        QT_MOC_LITERAL(145, 17),  // "saturationChanged"
        QT_MOC_LITERAL(163, 9),  // "saturated"
        QT_MOC_LITERAL(173, 16),  // "stabilityChanged"
        QT_MOC_LITERAL(190, 6),  // "stable"
        QT_MOC_LITERAL(197, 12),  // "processValue"
        QT_MOC_LITERAL(210, 12),  // "controlInput"
        QT_MOC_LITERAL(223, 11)   // "processType"
    },
    "ProcessModel",
    "processValueChanged",
    "",
    "value",
    "controlInputChanged",
    "input",
    "processTypeChanged",
    "ProcessType",
    "type",
    "parameterIdentified",
    "ModelParameters",
    "params",
    "saturationChanged",
    "saturated",
    "stabilityChanged",
    "stable",
    "processValue",
    "controlInput",
    "processType"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ProcessModel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       3,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    4 /* Public */,
       4,    1,   53,    2, 0x06,    6 /* Public */,
       6,    1,   56,    2, 0x06,    8 /* Public */,
       9,    1,   59,    2, 0x06,   10 /* Public */,
      12,    1,   62,    2, 0x06,   12 /* Public */,
      14,    1,   65,    2, 0x06,   14 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   15,

 // properties: name, type, flags
      16, QMetaType::Double, 0x00015001, uint(0), 0,
      17, QMetaType::Double, 0x00015103, uint(1), 0,
      18, 0x80000000 | 7, 0x0001510b, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProcessModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ProcessModel.offsetsAndSizes,
    qt_meta_data_ProcessModel,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ProcessModel_t,
        // property 'processValue'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'controlInput'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'processType'
        QtPrivate::TypeAndForceComplete<ProcessType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProcessModel, std::true_type>,
        // method 'processValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'controlInputChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'processTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ProcessType, std::false_type>,
        // method 'parameterIdentified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const ModelParameters &, std::false_type>,
        // method 'saturationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stabilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void ProcessModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProcessModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->processValueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->controlInputChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->processTypeChanged((*reinterpret_cast< std::add_pointer_t<ProcessType>>(_a[1]))); break;
        case 3: _t->parameterIdentified((*reinterpret_cast< std::add_pointer_t<ModelParameters>>(_a[1]))); break;
        case 4: _t->saturationChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->stabilityChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProcessModel::*)(double );
            if (_t _q_method = &ProcessModel::processValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProcessModel::*)(double );
            if (_t _q_method = &ProcessModel::controlInputChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProcessModel::*)(ProcessType );
            if (_t _q_method = &ProcessModel::processTypeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProcessModel::*)(const ModelParameters & );
            if (_t _q_method = &ProcessModel::parameterIdentified; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ProcessModel::*)(bool );
            if (_t _q_method = &ProcessModel::saturationChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ProcessModel::*)(bool );
            if (_t _q_method = &ProcessModel::stabilityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ProcessModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->getProcessValue(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->getControlInput(); break;
        case 2: *reinterpret_cast< ProcessType*>(_v) = _t->getProcessType(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ProcessModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setControlInput(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setProcessType(*reinterpret_cast< ProcessType*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *ProcessModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcessModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ProcessModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ProcessModel::processValueChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProcessModel::controlInputChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProcessModel::processTypeChanged(ProcessType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProcessModel::parameterIdentified(const ModelParameters & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ProcessModel::saturationChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ProcessModel::stabilityChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
