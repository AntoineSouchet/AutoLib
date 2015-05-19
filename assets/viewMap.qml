import bb.cascades 1.4

import bb.cascades.maps 1.0

Page {
    property alias latitude : mapview.latitude
    property alias longitude : mapview.longitude

    Container {
        id: root
        layout: DockLayout {
        }
        MapView {
            id: mapview
            altitude: 3000
            preferredWidth: 768
            preferredHeight: 1280
            onRequestRender: {
                pinContainer.addPin(mapview.latitude, mapview.longitude);
            }
            onCreationCompleted: {
                pinContainer.addPin(mapview.latitude, mapview.longitude);
            }
        }
        onCreationCompleted: {
            mapview.latitude =latitude
            mapview.longitude = longitude
            pinContainer.addPin(latitude, longitude);
        }

        Container {
            id: pinContainer
            // Must match the mapview width and height and position
            preferredHeight: 1280
            preferredWidth: 768
            //touchPropagationMode: TouchPropagationMode.PassThrough
            overlapTouchPolicy: OverlapTouchPolicy.Allow
            property variant currentBubble
            property variant me
            layout: AbsoluteLayout {
            }
            function addPin(lat, lon) {
                var marker = pin.createObject();
                marker.lat = lat;
                marker.lon = lon;
                var xy = _mapViewTest.worldToPixelInvokable(mapview, marker.lat, marker.lon);
                marker.x = xy[0];
                marker.y = xy[1];
                pinContainer.add(marker);
                marker.animDrop.play();
            }
            
            function showMe() {
                var marker = pin.createObject();
                marker.pinImageSource = "asset:///images/me.png"
                marker.pointerOffsetX = 30
                marker.pointerOffsetY = 30
                pinContainer.insert(-1, marker);
                marker.visible = false;
                me = marker;
            }
            function updateMarkers() {
                _mapViewTest.updateMarkers(mapview, pinContainer);
            }
            function removeBubble() {
                pinContainer.remove(currentBubble);
            }

        }
    }
    attachedObjects: [
        ComponentDefinition {
            id: pin
            source: "pin.qml"
        }
    ]
    onCreationCompleted: {
        pinContainer.addPin(mapview.latitude, mapview.longitude);
    }
}




