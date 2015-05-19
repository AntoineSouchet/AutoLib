/*
 * AutoLibMap.h
 *
 *  Created on: 19 mai 2015
 *      Author: as250818
 */

#ifndef AUTOLIBMAP_H_
#define AUTOLIBMAP_H_

    #include <QObject>
    #include <QVariant>

#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/MessageService>
#include <bb/platform/bbm/UserProfile>

    namespace bb {
    namespace cascades {
    class Application;
    namespace maps
            {
                class MapView;
            }
    }
    }

    class QPoint;

    /*!
     * @brief Application pane object
     *
     * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
     */
    class AutoLibMap: public QObject
    {
        Q_OBJECT

    public:
        AutoLibMap(bb::cascades::Application *app);

        Q_INVOKABLE QVariantList worldToPixelInvokable(QObject* mapObject, double latitude, double longitude) const;
        Q_INVOKABLE void updateMarkers(QObject* mapObject, QObject* containerObject) const;
        Q_INVOKABLE void addPoint(double longitude,double latitude);
        Q_INVOKABLE void Map();

    private:
        QPoint worldToPixel(QObject* mapObject, double latitude, double longitude) const;
        bb::cascades::maps::MapView* mapView;
    };

    #endif
