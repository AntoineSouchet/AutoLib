/****************************************************************************
** Meta object code from reading C++ file 'MapViewDemo.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MapViewDemo.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapViewDemo.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapViewDemo[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      55,   26,   13,   12, 0x02,
     127,  101,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_MapViewDemo[] = {
    "MapViewDemo\0\0QVariantList\0"
    "mapObject,latitude,longitude\0"
    "worldToPixelInvokable(QObject*,double,double)\0"
    "mapObject,containerObject\0"
    "updateMarkers(QObject*,QObject*)\0"
};

void MapViewDemo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MapViewDemo *_t = static_cast<MapViewDemo *>(_o);
        switch (_id) {
        case 0: { QVariantList _r = _t->worldToPixelInvokable((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 1: _t->updateMarkers((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MapViewDemo::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MapViewDemo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MapViewDemo,
      qt_meta_data_MapViewDemo, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapViewDemo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapViewDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapViewDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapViewDemo))
        return static_cast<void*>(const_cast< MapViewDemo*>(this));
    return QObject::qt_metacast(_clname);
}

int MapViewDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
