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

#include <QPoint>

    using namespace bb::cascades;
    using namespace bb::cascades::maps;
    using namespace bb::platform::geo;
    using namespace bb::system;
    using namespace bb::data;


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
