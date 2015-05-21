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

#include <QtLocationSubset/QGeoPositionInfo>
#include <QtLocationSubset/QGeoPositionInfoSource>
#include <QtNetwork>

using namespace QtMobilitySubset;
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
        Q_INVOKABLE void CallWebServiceWithCoord(QString latitude,QString longitude);
        Q_INVOKABLE  void getWsInformations(QNetworkReply*);

    private:
        QGeoPositionInfoSource *locationDataSource;

        void finished(QNetworkReply*);
    };

    #endif
