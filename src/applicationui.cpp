/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/Container>
#include <bb/cascades/maps/MapView>
#include <bb/cascades/maps/MapData>
#include <bb/cascades/maps/DataProvider>
#include <bb/cascades/QmlDocument>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/GeoLocation>
#include <bb/platform/geo/Marker>
#include <bb/UIToolkitSupport>
#include <bb/cascades/LocaleHandler>

using namespace bb;
using namespace bb::cascades;
using namespace bb::cascades::maps;
using namespace bb::platform::geo;


ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_mapViewTest", this);
    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    QObject* mapViewAsQObject =
                  root->findChild<QObject*>(QString("mapViewObj"));
          if (mapViewAsQObject) {
              mapView =
                qobject_cast<bb::cascades::maps::MapView*>(mapViewAsQObject);
              mapView->setCaptionGoButtonVisible(true);
              if (mapView) {

                  // Create a data provider just for the device location
                  // object. That way, when the clear function is called,
                  // this object is not removed.
                  DataProvider* deviceLocDataProv =
                    new DataProvider("device-location-data-provider");
                  mapView->mapData()->addProvider(deviceLocDataProv);

                  // Create a geolocation just for the device's location.
                  deviceLocation = new GeoLocation("device-location-id");
                  deviceLocation->setName("Current Device Location");
                  deviceLocation->setDescription("<html><a href=\"http://www.blackberry.com\">Hyperlinks</a> are super useful in bubbles.</html>");

                  // For that location, replace the standard default
                  // pin with the provided bulls eye asset.
                  Marker bullseye = Marker(UIToolkitSupport::absolutePathFromUrl(
                     QUrl("asset:///images/me.png")), QSize(60, 60),
                     QPoint(29, 29), QPoint(29, 1));
                  deviceLocation->setMarker(bullseye);

                  deviceLocDataProv->add(deviceLocation);
              }
          }

          // set created root object as a scene
          bb::cascades::Application::instance()->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("AutoLib_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::addPinAtCurrentMapCenter() {
    if (mapView) {
        GeoLocation* newDrop = new GeoLocation();
        newDrop->setLatitude(mapView->latitude());
        newDrop->setLongitude(mapView->longitude());
        QString desc =
          QString("Coordinates: %1, %2").arg(mapView->latitude(),
            0, 'f', 3).arg(mapView->longitude(), 0, 'f', 3);
        newDrop->setName("Dropped Pin");
        newDrop->setDescription(desc);

        // Use the marker in the assets, as opposed to
        // the default marker
        Marker flag;
        flag.setIconUri(UIToolkitSupport::absolutePathFromUrl(
                        QUrl("asset:///images/on_map_pin.png")));
        flag.setIconSize(QSize(60, 60));
        flag.setLocationCoordinate(QPoint(20, 59));
        flag.setCaptionTailCoordinate(QPoint(20, 1));
        newDrop->setMarker(flag);

        mapView->mapData()->add(newDrop);
    }
}
