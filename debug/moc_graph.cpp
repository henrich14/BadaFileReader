/****************************************************************************
** Meta object code from reading C++ file 'graph.h'
**
** Created: Sat 23. Jan 20:48:14 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../graph.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graph[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,    7,    6,    6, 0x08,
      42,    6,    6,    6, 0x08,
      68,   62,    6,    6, 0x08,
      93,   62,    6,    6, 0x08,
     118,   62,    6,    6, 0x08,
     143,   62,    6,    6, 0x08,
     168,   62,    6,    6, 0x08,
     193,   62,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Graph[] = {
    "Graph\0\0DATA\0receive_data(QVector<double>)\0"
    "startClicked_slot()\0value\0"
    "combo_1_clicked(QString)\0"
    "combo_2_clicked(QString)\0"
    "combo_3_clicked(QString)\0"
    "combo_4_clicked(QString)\0"
    "combo_5_clicked(QString)\0"
    "combo_6_clicked(QString)\0"
};

void Graph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Graph *_t = static_cast<Graph *>(_o);
        switch (_id) {
        case 0: _t->receive_data((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 1: _t->startClicked_slot(); break;
        case 2: _t->combo_1_clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->combo_2_clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->combo_3_clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->combo_4_clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->combo_5_clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->combo_6_clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Graph::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Graph::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Graph,
      qt_meta_data_Graph, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graph::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graph))
        return static_cast<void*>(const_cast< Graph*>(this));
    return QDialog::qt_metacast(_clname);
}

int Graph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
