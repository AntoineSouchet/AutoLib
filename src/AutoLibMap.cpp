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

    #include <QPoint>

    using namespace bb::cascades;
    using namespace bb::cascades::maps;
    using namespace bb::platform::geo;


    AutoLibMap::AutoLibMap(bb::cascades::Application *app) :
                    QObject(app)
            {
                // create scene document from main.qml asset
                // set parent to created document to ensure it exists for the whole application lifetime
                QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
                qml->setContextProperty("_mapViewTest", this);

                // create root object for the UI
                AbstractPane *root = qml->createRootObject<AbstractPane>();
                QObject* mapViewAsQObject = root->findChild<QObject*>(QString("mapViewObj"));
                mapView = qobject_cast<bb::cascades::maps::MapView*>(mapViewAsQObject);
                // set created root object as a scene
                app->setScene(root);
            }

    void AutoLibMap::Map()
    {
        InvokeManager invokeManager;
        InvokeRequest request;
        request.setAction("bb.action.OPEN");
        invokeManager.invoke(request);
    }

    void AutoLibMap::addPoint(double longitude,double latitude)
    {
        latitude = 38.134557;
        longitude =  -81.123047;

       // qml->setContextProperty("_mapViewTest", this);



                                        //mapView = root->findChild<MapView*>("mapViewObj");
        mapView->setAltitude(413);
        mapView -> setLatitude(38.134557);
        mapView -> setLongitude(-81.123047);
        mapView->setLocationOnVisible();
        mapView->setVisible(true);

        // Create an instance of Marker to represent the pin
        Marker purpleMarker;
        purpleMarker.setIconUri( "asset://images/on_map_pin.png" );
        purpleMarker.setIconSize( QSize( 64, 64 ) );

        // Offset the location coordinates so that it's near the bottom
        // and center of the icon (that is, the pin's point)
        purpleMarker.setLocationCoordinate( QPoint( 24, 64 ) );

        // Set the position on the icon so that the caption bubble's
        // tail points to the top center of the pin
        purpleMarker.setCaptionTailCoordinate( QPoint( 24, 3 ) );

        // Create the GeoLocation object and set the marker
        GeoLocation* ottawa = new GeoLocation(
                "id-ottawa",
                "Ottawa",
                Point( 38.134557, -81.123047 ) );

        ottawa->setMarker( purpleMarker );

        // Add the location to your map
        mapView->mapData()->add( ottawa );

        // When your location is within the map's viewport,
        // you will see the custom icon
        mapView->setLocationOnVisible();
        // Add the MapView to the root Page
        Page *page = new Page();
        page->setContent(mapView);
//            app->setScene(page);

    }

    QVariantList AutoLibMap::worldToPixelInvokable(QObject* mapObject, double latitude, double longitude) const
       {
           MapView* mapview = qobject_cast<MapView*>(mapObject);
           const Point worldCoordinates = Point(latitude, longitude);
           const QPoint pixels = mapview->worldToWindow(worldCoordinates);

           return QVariantList() << pixels.x() << pixels.y();
       }

       void AutoLibMap::updateMarkers(QObject* mapObject, QObject* containerObject) const
       {
           MapView* mapview = qobject_cast<MapView*>(mapObject);
           Container* container = qobject_cast<Container*>(containerObject);

           for (int i = 0; i < container->count(); i++) {
               const QPoint xy = worldToPixel(mapview,
                                              container->at(i)->property("lat").value<double>(),
                                              container->at(i)->property("lon").value<double>());
               container->at(i)->setProperty("x", xy.x());
               container->at(i)->setProperty("y", xy.y());
           }
       }

       QPoint AutoLibMap::worldToPixel(QObject* mapObject, double latitude, double longitude) const
       {
           MapView* mapview = qobject_cast<MapView*>(mapObject);
           const Point worldCoordinates = Point(latitude, longitude);

           return mapview->worldToWindow(worldCoordinates);
       }
