/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onAnimationTimer",
        "",
        "updateStatus",
        "onCreateRectangle",
        "onCreateCar",
        "onMoveRectangle",
        "onChangeRectangleColor",
        "onSaveRectangle",
        "onLoadRectangle",
        "onToggleLeftDoor",
        "onToggleRightDoor",
        "onToggleHeadlights",
        "onOpenAllDoors",
        "onCloseAllDoors",
        "onStartEngine",
        "onStopEngine",
        "onParkCar",
        "onChangeCarColor",
        "onChangeWheelColor",
        "onSaveCar",
        "onLoadCar",
        "onMoveLeft",
        "onMoveRight",
        "onMoveUp",
        "onMoveDown",
        "onStopMovement",
        "onResetPosition",
        "onErrorOccurred",
        "message",
        "onAbout",
        "onHelp",
        "onEngineStateChanged",
        "running",
        "onCarStateChanged",
        "CarState",
        "newState"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAnimationTimer'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateStatus'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCreateRectangle'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCreateCar'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveRectangle'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChangeRectangleColor'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSaveRectangle'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLoadRectangle'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onToggleLeftDoor'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onToggleRightDoor'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onToggleHeadlights'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onOpenAllDoors'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCloseAllDoors'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStartEngine'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStopEngine'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onParkCar'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChangeCarColor'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChangeWheelColor'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSaveCar'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLoadCar'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveLeft'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveRight'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveUp'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMoveDown'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStopMovement'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onResetPosition'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onErrorOccurred'
        QtMocHelpers::SlotData<void(const QString &)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 29 },
        }}),
        // Slot 'onAbout'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onHelp'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onEngineStateChanged'
        QtMocHelpers::SlotData<void(bool)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 33 },
        }}),
        // Slot 'onCarStateChanged'
        QtMocHelpers::SlotData<void(CarState)>(34, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 35, 36 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAnimationTimer(); break;
        case 1: _t->updateStatus(); break;
        case 2: _t->onCreateRectangle(); break;
        case 3: _t->onCreateCar(); break;
        case 4: _t->onMoveRectangle(); break;
        case 5: _t->onChangeRectangleColor(); break;
        case 6: _t->onSaveRectangle(); break;
        case 7: _t->onLoadRectangle(); break;
        case 8: _t->onToggleLeftDoor(); break;
        case 9: _t->onToggleRightDoor(); break;
        case 10: _t->onToggleHeadlights(); break;
        case 11: _t->onOpenAllDoors(); break;
        case 12: _t->onCloseAllDoors(); break;
        case 13: _t->onStartEngine(); break;
        case 14: _t->onStopEngine(); break;
        case 15: _t->onParkCar(); break;
        case 16: _t->onChangeCarColor(); break;
        case 17: _t->onChangeWheelColor(); break;
        case 18: _t->onSaveCar(); break;
        case 19: _t->onLoadCar(); break;
        case 20: _t->onMoveLeft(); break;
        case 21: _t->onMoveRight(); break;
        case 22: _t->onMoveUp(); break;
        case 23: _t->onMoveDown(); break;
        case 24: _t->onStopMovement(); break;
        case 25: _t->onResetPosition(); break;
        case 26: _t->onErrorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->onAbout(); break;
        case 28: _t->onHelp(); break;
        case 29: _t->onEngineStateChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 30: _t->onCarStateChanged((*reinterpret_cast<std::add_pointer_t<CarState>>(_a[1]))); break;
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
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 31;
    }
    return _id;
}
QT_WARNING_POP
