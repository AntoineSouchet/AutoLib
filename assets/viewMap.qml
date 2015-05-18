import bb.cascades 1.4

import bb.cascades.maps 1.0


Page {
    property alias latitude : mapview.latitude
    property alias longitude : mapview.longitude
    
    MapView {

        id: mapview
        altitude: 3000
        
    }
    onCreationCompleted: {
        _mapViewTest.addPinAtCurrentMapCenter();
    }
}
