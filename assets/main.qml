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

import bb.cascades 1.3
import bb.data 1.0
import bb.cascades.maps 1.0

NavigationPane {
    
    id: nav
    Menu.definition: MenuDefinition {        
        actions: [
            ActionItem {
                title: "A propos"
//                onTriggered: {
//                    var page = proposPages.createObject();
//                    nav.push(page);
//                }
            },
            ActionItem {
                title: "Partager"

            },
            ActionItem {
                title: "Noter"

            }
        ] 
    } 
    
Page {
    titleBar: 
    TitleBar {
        title : "Auto lib Paris"        
    }
    Container {
    Label {
        id: rechercheDep
        text:"Recherhe par département : "
    }
        TextField {
            id:departement
        }
        Button {
            text:"Rechercher"
           onClicked: {
           listautolib.visible = false
           myIndicator.visible = true
           dataSource.source = "http://public.opendatasoft.com/api/records/1.0/search?dataset=stations_et_espaces_autolib_de_la_metropole_parisienne&q=" + departement.text + "&facet=identifiant_autolib&facet=code_postal&facet=ville&facet=emplacement"
           dataSource.load()
           listautolib.visible = true
           }
        }
        
//        MapView {
//            id: mapview
//            altitude: 3000
//            latitude: 45.342614
//            longitude: -75.914991
//        }
        
        ActivityIndicator {
            id: myIndicator
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            minHeight: 200
            minWidth: 200
            visible: false
            accessibility.name: "myIndicator"
        }
        ListView {
            id:listautolib
            dataModel: dataModel 
            //visible: false
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    
                    content: Container {            
                        Container {
                            layout: StackLayout {
                                orientation: LayoutOrientation.TopToBottom
                            }
                            Label {
                                id: idAuto
                                multiline: true
                                horizontalAlignment: HorizontalAlignment.Center
                                text: "Identifiant : " + ListItemData.fields.identifiant_autolib
                            }
                            Label {
                                id: emplacementAuto
                                multiline: true
                                horizontalAlignment: HorizontalAlignment.Center
                                text: "Emplacement : " + ListItemData.fields.emplacement
                            }
                            Label {
                                id: codeAuto
                                multiline: true
                                horizontalAlignment: HorizontalAlignment.Center
                                text: "Code postal : " + ListItemData.fields.code_postal
                            }
                            Label {
                                id: rueAuto
                                multiline: true
                                horizontalAlignment: HorizontalAlignment.Center
                                text:  "Rue : " + ListItemData.fields.rue
                            }
                            Label {
                                id: x
                                text : ListItemData.fields.field13[0]
                           
                                visible: false
                            }
                            
                            Label {
                                id: y
                                text : ListItemData.fields.field13[1]
                                visible: false
                            }

                            Container {
                                layout: StackLayout {
                                    orientation: LayoutOrientation.TopToBottom
                                }
                            }
                        }
                    }
                }
                
            ]
            accessibility.name: "FirstListView"
onTriggered: {
    var selectedItem = dataModel.data(indexPath);
    var page = mapPages.createObject();
    page.latitude = selectedItem.fields.field13[0];
    page.longitude = selectedItem.fields.field13[1];
    nav.push(page);
}
        } 
        
    }
    
    attachedObjects: [
        ComponentDefinition {
            id: mapPages
            source: "viewMap.qml"
        },
        GroupDataModel {
            id: dataModel
            sortedAscending: false
            grouping: ItemGrouping.ByFullValue

        },
    DataSource {
        id: dataSource
        type: DataSourceType.Json
        source: "http://public.opendatasoft.com/api/records/1.0/search?dataset=stations_et_espaces_autolib_de_la_metropole_parisienne&q=75010&facet=identifiant_autolib&facet=code_postal&facet=ville&facet=emplacement"
       // source : "http://www.blackberry-10.fr/jsonfile_last10.php"
        remote: true    
    onDataLoaded: {
        dataModel.clear(); 
        dataModel.insertList(data.records);
        myIndicator.visible = false;
    }
    } 
    
    ] 
    onCreationCompleted: {

        dataSource.load();
    }
} 
}
