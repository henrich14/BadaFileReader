/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created: Wed 2. Mar 19:10:50 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Dialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,    8,    7,    7, 0x05,
      40,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,    7,    7,    7, 0x08,
      71,    7,    7,    7, 0x08,
      90,    7,    7,    7, 0x08,
     106,    7,    7,    7, 0x08,
     126,    7,    7,    7, 0x08,
     154,    7,    7,    7, 0x08,
     164,    7,    7,    7, 0x08,
     180,    7,    7,    7, 0x08,
     208,  195,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Dialog[] = {
    "Dialog\0\0DATA\0send_data(QVector<double>)\0"
    "start_signal()\0parse_clicked()\0"
    "CASMACH_selected()\0ROCD_selected()\0"
    "Gradient_selected()\0EmergencyDescent_selected()\0"
    "TimeOut()\0start_clicked()\0stop_clicked()\0"
    "ICAOFileCode\0AircraftChanged(QString)\0"
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Dialog *_t = static_cast<Dialog *>(_o);
        switch (_id) {
        case 0: _t->send_data((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 1: _t->start_signal(); break;
        case 2: _t->parse_clicked(); break;
        case 3: _t->CASMACH_selected(); break;
        case 4: _t->ROCD_selected(); break;
        case 5: _t->Gradient_selected(); break;
        case 6: _t->EmergencyDescent_selected(); break;
        case 7: _t->TimeOut(); break;
        case 8: _t->start_clicked(); break;
        case 9: _t->stop_clicked(); break;
        case 10: _t->AircraftChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Dialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog,
      qt_meta_data_Dialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog))
        return static_cast<void*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Dialog::send_data(const QVector<double> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dialog::start_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
