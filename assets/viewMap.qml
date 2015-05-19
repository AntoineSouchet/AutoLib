import bb.cascades 1.4

import bb.cascades.maps 1.0

Page {
    property alias latitude : test.text
    property alias longitude : test.text

    Container {
        id: root
        layout: DockLayout {
        }
        Label {
            id:test
            visible: false
        }
        MapView {
            id: mapview
            altitude: 3000
            preferredWidth: 768
            preferredHeight: 1280
            objectName: "mapViewObj"
        }
        onCreationCompleted: {
            _mapViewTest.addPoint(longitude, latitude);
        }

}
}




