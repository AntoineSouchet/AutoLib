/****************************************************************************
** Meta object code from reading C++ file 'AutoLibMap.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/AutoLibMap.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AutoLibMap.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AutoLibMap[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      54,   25,   12,   11, 0x02,
     126,  100,   11,   11, 0x02,
     178,  159,   11,   11, 0x02,
     202,   11,   11,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_AutoLibMap[] = {
    "AutoLibMap\0\0QVariantList\0"
    "mapObject,latitude,longitude\0"
    "worldToPixelInvokable(QObject*,double,double)\0"
    "mapObject,containerObject\0"
    "updateMarkers(QObject*,QObject*)\0"
    "longitude,latitude\0addPoint(double,double)\0"
    "Map()\0"
};

void AutoLibMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AutoLibMap *_t = static_cast<AutoLibMap *>(_o);
        switch (_id) {
        case 0: { QVariantList _r = _t->worldToPixelInvokable((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 1: _t->updateMarkers((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 2: _t->addPoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->Map(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AutoLibMap::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AutoLibMap::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AutoLibMap,
      qt_meta_data_AutoLibMap, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AutoLibMap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AutoLibMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AutoLibMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AutoLibMap))
        return static_cast<void*>(const_cast< AutoLibMap*>(this));
    return QObject::qt_metacast(_clname);
}

int AutoLibMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
