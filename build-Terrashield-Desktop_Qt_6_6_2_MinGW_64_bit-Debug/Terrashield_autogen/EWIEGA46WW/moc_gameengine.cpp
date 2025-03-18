/****************************************************************************
** Meta object code from reading C++ file 'gameengine.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Terrashield/gameengine.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGameEngineENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSGameEngineENDCLASS = QtMocHelpers::stringData(
    "GameEngine",
    "updateAllPositions",
    "",
    "loadMap",
    "worldName",
    "animate",
    "retryMap",
    "closePause",
    "openMenu",
    "quitApp",
    "restart"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGameEngineENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[11];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[10];
    char stringdata5[8];
    char stringdata6[9];
    char stringdata7[11];
    char stringdata8[9];
    char stringdata9[8];
    char stringdata10[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGameEngineENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGameEngineENDCLASS_t qt_meta_stringdata_CLASSGameEngineENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "GameEngine"
        QT_MOC_LITERAL(11, 18),  // "updateAllPositions"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 7),  // "loadMap"
        QT_MOC_LITERAL(39, 9),  // "worldName"
        QT_MOC_LITERAL(49, 7),  // "animate"
        QT_MOC_LITERAL(57, 8),  // "retryMap"
        QT_MOC_LITERAL(66, 10),  // "closePause"
        QT_MOC_LITERAL(77, 8),  // "openMenu"
        QT_MOC_LITERAL(86, 7),  // "quitApp"
        QT_MOC_LITERAL(94, 7)   // "restart"
    },
    "GameEngine",
    "updateAllPositions",
    "",
    "loadMap",
    "worldName",
    "animate",
    "retryMap",
    "closePause",
    "openMenu",
    "quitApp",
    "restart"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGameEngineENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x0a,    1 /* Public */,
       3,    1,   63,    2, 0x0a,    2 /* Public */,
       5,    0,   66,    2, 0x0a,    4 /* Public */,
       6,    0,   67,    2, 0x0a,    5 /* Public */,
       7,    0,   68,    2, 0x0a,    6 /* Public */,
       8,    0,   69,    2, 0x0a,    7 /* Public */,
       9,    0,   70,    2, 0x0a,    8 /* Public */,
      10,    0,   71,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_CLASSGameEngineENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGameEngineENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGameEngineENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameEngine, std::true_type>,
        // method 'updateAllPositions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadMap'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'animate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'retryMap'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closePause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitApp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GameEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameEngine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateAllPositions(); break;
        case 1: _t->loadMap((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->animate(); break;
        case 3: _t->retryMap(); break;
        case 4: _t->closePause(); break;
        case 5: _t->openMenu(); break;
        case 6: _t->quitApp(); break;
        case 7: _t->restart(); break;
        default: ;
        }
    }
}

const QMetaObject *GameEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGameEngineENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int GameEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
    }
    return _id;
}
QT_WARNING_POP
