/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
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
        "newFile",
        "",
        "openFile",
        "saveFile",
        "saveAsFile",
        "exportImage",
        "exitApplication",
        "copyFigure",
        "pasteFigure",
        "deleteFigure",
        "selectAll",
        "deselectAll",
        "createFigure",
        "createFigureFromType",
        "type",
        "removeSelectedFigure",
        "clearAllFigures",
        "updateFigureInfo",
        "updateSelectedFigure",
        "updateFigureList",
        "setDrawTriangleMode",
        "setDrawRectangleMode",
        "setDrawSquareMode",
        "setDrawCircleMode",
        "setDrawEllipseMode",
        "setDrawRhombusMode",
        "setDrawHexagonMode",
        "setDrawStarMode",
        "setDrawPolygonMode",
        "stopDrawingMode",
        "applyTransformation",
        "animateTransformation",
        "stopAnimation",
        "updateAnimationProgress",
        "progress",
        "chooseLineColor",
        "chooseFillColor",
        "updateLineWidth",
        "updateSpecificParameter",
        "updateVertex",
        "moveCenterToPoint",
        "showCenterInfo",
        "toggleGrid",
        "enabled",
        "toggleCenters",
        "toggleTriangulation",
        "toggleVertices",
        "toggleBoundingBox",
        "toggleSnapToGrid",
        "zoomIn",
        "zoomOut",
        "resetView",
        "fitToView",
        "showFullScreen",
        "calculateTotalArea",
        "calculateTotalPerimeter",
        "showFigureStatistics",
        "about",
        "showHelp",
        "showShortcuts"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'newFile'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'openFile'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveFile'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveAsFile'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'exportImage'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'exitApplication'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'copyFigure'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'pasteFigure'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'deleteFigure'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'selectAll'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'deselectAll'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'createFigure'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'createFigureFromType'
        QtMocHelpers::SlotData<void(const QString &)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'removeSelectedFigure'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'clearAllFigures'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateFigureInfo'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateSelectedFigure'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateFigureList'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawTriangleMode'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawRectangleMode'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawSquareMode'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawCircleMode'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawEllipseMode'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawRhombusMode'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawHexagonMode'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawStarMode'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setDrawPolygonMode'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'stopDrawingMode'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'applyTransformation'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'animateTransformation'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'stopAnimation'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateAnimationProgress'
        QtMocHelpers::SlotData<void(double)>(34, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 35 },
        }}),
        // Slot 'chooseLineColor'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'chooseFillColor'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateLineWidth'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateSpecificParameter'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateVertex'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'moveCenterToPoint'
        QtMocHelpers::SlotData<void()>(41, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showCenterInfo'
        QtMocHelpers::SlotData<void()>(42, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'toggleGrid'
        QtMocHelpers::SlotData<void(bool)>(43, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 44 },
        }}),
        // Slot 'toggleCenters'
        QtMocHelpers::SlotData<void(bool)>(45, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 44 },
        }}),
        // Slot 'toggleTriangulation'
        QtMocHelpers::SlotData<void(bool)>(46, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 44 },
        }}),
        // Slot 'toggleVertices'
        QtMocHelpers::SlotData<void(bool)>(47, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 44 },
        }}),
        // Slot 'toggleBoundingBox'
        QtMocHelpers::SlotData<void(bool)>(48, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 44 },
        }}),
        // Slot 'toggleSnapToGrid'
        QtMocHelpers::SlotData<void(bool)>(49, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 44 },
        }}),
        // Slot 'zoomIn'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'zoomOut'
        QtMocHelpers::SlotData<void()>(51, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'resetView'
        QtMocHelpers::SlotData<void()>(52, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'fitToView'
        QtMocHelpers::SlotData<void()>(53, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showFullScreen'
        QtMocHelpers::SlotData<void()>(54, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'calculateTotalArea'
        QtMocHelpers::SlotData<void()>(55, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'calculateTotalPerimeter'
        QtMocHelpers::SlotData<void()>(56, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showFigureStatistics'
        QtMocHelpers::SlotData<void()>(57, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'about'
        QtMocHelpers::SlotData<void()>(58, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showHelp'
        QtMocHelpers::SlotData<void()>(59, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showShortcuts'
        QtMocHelpers::SlotData<void()>(60, 2, QMC::AccessPrivate, QMetaType::Void),
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
        case 0: _t->newFile(); break;
        case 1: _t->openFile(); break;
        case 2: _t->saveFile(); break;
        case 3: _t->saveAsFile(); break;
        case 4: _t->exportImage(); break;
        case 5: _t->exitApplication(); break;
        case 6: _t->copyFigure(); break;
        case 7: _t->pasteFigure(); break;
        case 8: _t->deleteFigure(); break;
        case 9: _t->selectAll(); break;
        case 10: _t->deselectAll(); break;
        case 11: _t->createFigure(); break;
        case 12: _t->createFigureFromType((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->removeSelectedFigure(); break;
        case 14: _t->clearAllFigures(); break;
        case 15: _t->updateFigureInfo(); break;
        case 16: _t->updateSelectedFigure(); break;
        case 17: _t->updateFigureList(); break;
        case 18: _t->setDrawTriangleMode(); break;
        case 19: _t->setDrawRectangleMode(); break;
        case 20: _t->setDrawSquareMode(); break;
        case 21: _t->setDrawCircleMode(); break;
        case 22: _t->setDrawEllipseMode(); break;
        case 23: _t->setDrawRhombusMode(); break;
        case 24: _t->setDrawHexagonMode(); break;
        case 25: _t->setDrawStarMode(); break;
        case 26: _t->setDrawPolygonMode(); break;
        case 27: _t->stopDrawingMode(); break;
        case 28: _t->applyTransformation(); break;
        case 29: _t->animateTransformation(); break;
        case 30: _t->stopAnimation(); break;
        case 31: _t->updateAnimationProgress((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 32: _t->chooseLineColor(); break;
        case 33: _t->chooseFillColor(); break;
        case 34: _t->updateLineWidth(); break;
        case 35: _t->updateSpecificParameter(); break;
        case 36: _t->updateVertex(); break;
        case 37: _t->moveCenterToPoint(); break;
        case 38: _t->showCenterInfo(); break;
        case 39: _t->toggleGrid((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 40: _t->toggleCenters((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 41: _t->toggleTriangulation((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 42: _t->toggleVertices((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 43: _t->toggleBoundingBox((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 44: _t->toggleSnapToGrid((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 45: _t->zoomIn(); break;
        case 46: _t->zoomOut(); break;
        case 47: _t->resetView(); break;
        case 48: _t->fitToView(); break;
        case 49: _t->showFullScreen(); break;
        case 50: _t->calculateTotalArea(); break;
        case 51: _t->calculateTotalPerimeter(); break;
        case 52: _t->showFigureStatistics(); break;
        case 53: _t->about(); break;
        case 54: _t->showHelp(); break;
        case 55: _t->showShortcuts(); break;
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
        if (_id < 56)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 56;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 56)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 56;
    }
    return _id;
}
QT_WARNING_POP
