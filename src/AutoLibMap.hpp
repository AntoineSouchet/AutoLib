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
#include <QtLocationSubset/QGeoPositionInfo>

    namespace bb {
    namespace cascades {
    class Application;
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
        Q_INVOKABLE void Map(double latitude,double longitude,QString adresse);
        Q_INVOKABLE void MoreNear(double latitude,double longitude,QString adresse);
        Q_INVOKABLE void positionUpdated(QGeoPositionInfo geoPositionInfo);
        Q_INVOKABLE void startGPS();
    private:

    };

    #endif
