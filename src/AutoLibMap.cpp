/*
 * AutoLibMap.cpp
 *
 *  Created on: 19 mai 2015
 *      Author: as250818
 */

#include "AutoLibMap.hpp"
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/Container>
#include <bb/cascades/maps/MapView>
#include <bb/cascades/QmlDocument>
#include <bb/platform/geo/Point.hpp>
#include <bb/cascades/LocaleHandler>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <bb/cascades/Page>
#include <bb/cascades/maps/MapData>
#include <bb/platform/geo/Marker>
#include <bb/platform/geo/GeoLocation>
#include <bb/data/JsonDataAccess>
#include <QtLocationSubset/QGeoPositionInfo>
#include <QtNetwork>

#include <QPoint>

    using namespace bb::cascades;
    using namespace bb::cascades::maps;
    using namespace bb::platform::geo;
    using namespace bb::system;
    using namespace bb::data;
    using namespace QtMobilitySubset;


    AutoLibMap::AutoLibMap(bb::cascades::Application *app) :
                    QObject(app)
            {
                // create scene document from main.qml asset
                // set parent to created document to ensure it exists for the whole application lifetime
                QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
                qml->setContextProperty("_mapViewTest", this);

                // create root object for the UI
                AbstractPane *root = qml->createRootObject<AbstractPane>();
                // set created root object as a scene
                app->setScene(root);
            }

    void GetMoreNearStation()
    {

    }


    void AutoLibMap::positionUpdated(QGeoPositionInfo geoPositionInfo) {

        if (geoPositionInfo.isValid()) {
            // We've got the position. No need to continue the listening.
            locationDataSource->stopUpdates();

            // Save the position information into a member variable
            QGeoPositionInfo myPositionInfo = geoPositionInfo;

            // Get the current location as latitude and longitude
            QGeoCoordinate geoCoordinate = geoPositionInfo.coordinate();
            qreal latitude = geoCoordinate.latitude();
            qreal longitude = geoCoordinate.longitude();

            qDebug()<< QString("Latitude: %1 Longitude: %2").arg(latitude).arg(longitude);
            CallWebServiceWithCoord(latitude,longitude);
        }

    }

    void AutoLibMap::CallWebServiceWithCoord(double latitude,double longitude)
    {
        QString url = "http://public.opendatasoft.com/api/records/1.0/search?dataset=stations_et_espaces_autolib_de_la_metropole_parisienne&lang=FR&rows=1&facet=identifiant_autolib&facet=code_postal&facet=ville&facet=emplacement&geofilter.distance=48.8587455%2C+2.5101638%2C20000";
        QNetworkRequest request = QNetworkRequest();
        request.setUrl(QUrl(url));
        QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
            connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getWsInformations(QNetworkReply*)));
            networkAccessManager->get(request);
    }


    void AutoLibMap::getWsInformations(QNetworkReply* reply){

        qDebug() << "getWsInformations ! ";
        if (reply->error() == QNetworkReply::NoError)
          {
            qDebug() << "Read all and create JSON file ! ";
            QString mJsonData = reply->readAll();
            JsonDataAccess jda;
            qDebug() << mJsonData;
            QVariant mainList = jda.loadFromBuffer(mJsonData);
          }
          reply->deleteLater();
        }


    void AutoLibMap::startGPS() {

        qDebug() << " << starting GPS >>";

        // Obtain the location data source if it is not obtained already
        if (locationDataSource) {
            locationDataSource = QGeoPositionInfoSource::createDefaultSource(this);
            // Whenever the location data source signals that the current
            // position is updated, the positionUpdated function is called
            connect(locationDataSource, SIGNAL(positionUpdated(QGeoPositionInfo)),this, SLOT(positionUpdated(QGeoPositionInfo)));

            // Start listening for position updates
            locationDataSource->startUpdates();
        }
    }


    void AutoLibMap::MoreNear(double latitude,double longitude,QString adresse)
    {
        InvokeManager invokeManager;
        InvokeRequest request;
        request.setAction("bb.action.OPEN");
        request.setMimeType("application/vnd.rim.map.action-v1");
        QVariantMap navendData;
        navendData["latitude"] = latitude;
        navendData["longitude"] = longitude;
        navendData["properties.name"] = "AutoLib'";
        navendData["properties.description"] = adresse;

        QVariantMap data;
        data["view_mode"] = "nav";
        data["nav_end"] = navendData;

        JsonDataAccess jda;
                QByteArray buffer;

                jda.saveToBuffer(data, &buffer);
                request.setData(buffer);
                invokeManager.invoke(request);
    }
    void AutoLibMap::Map(double latitude,double longitude,QString adresse)
    {
        InvokeManager invokeManager;
        InvokeRequest request;
        request.setAction("bb.action.OPEN");
        request.setMimeType("application/vnd.rim.map.action-v1");
        QVariantMap centerData;
        centerData["latitude"] = latitude;
        centerData["longitude"] = longitude;

        QVariantMap placemarkData;
        placemarkData["latitude"] = latitude;
        placemarkData["longitude"] = longitude;
        placemarkData["name"] = "Station AutoLib'";
        placemarkData["description"] = adresse;

        QVariantMap data;
        data["view_mode"] = "map";
        data["center"] = centerData;
        data["placemark"] = placemarkData;
        JsonDataAccess jda;
        QByteArray buffer;

        jda.saveToBuffer(data, &buffer);
        request.setData(buffer);
        invokeManager.invoke(request);
    }
