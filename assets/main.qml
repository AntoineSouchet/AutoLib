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
    
Page {
    titleBar: 
    TitleBar {
        title : "Auto lib Paris"        
    }
    Container {

    Label {
        id: rechercheDep
        text:"Saisir le numéro de département : "
        horizontalAlignment: HorizontalAlignment.Center
    }
        TextField {
            id:departement
            text: "92330"
            accessibility.name: "departement TextField"
            }
        Label {
            id:error
            visible: false
        }
        Button {
            text:"Rechercher"
            horizontalAlignment: HorizontalAlignment.Center
           onClicked: {
               if(departement.text != "")
               {
                   error.visible = false;
                   myIndicator.visible = true
                   dataSource.source = "http://public.opendatasoft.com/api/records/1.0/search?dataset=stations_et_espaces_autolib_de_la_metropole_parisienne&q=" +departement.text + "&facet=identifiant_autolib&facet=code_postal&facet=ville&facet=emplacement"
                   dataSource.load()
               }
               else 
               {
                   error.visible = true;
                   error.text = "Merci de saisir un département.";
               }

           }
        }
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
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    StandardListItem {
                        title: ListItemData.fields.ville
                        description: ListItemData.fields.rue
                        status: ListItemData.fields.code_postal
                    }
                }
                
            ]
            accessibility.name: "FirstListView"
                onTriggered: {
                    var selectedItem = dataModel.data(indexPath);
                    _mapViewTest.Map(selectedItem.fields.field13[0], selectedItem.fields.field13[1],selectedItem.fields.rue);
                    }
        }           
    }
    actions: [                         

        ActionItem {
            title: "Géo-localisation"
            ActionBar.placement: ActionBarPlacement.Signature
            imageSource: "asset:///images/ic_map.png"
            onTriggered: {

            }
        },
        ActionItem {
            title: "Departement"
            imageSource: "asset:///images/ic_search.png"
            ActionBar.placement: ActionBarPlacement.Signature
            onTriggered: {
            
            }
        },
        InvokeActionItem {

            query {
                mimeType: "text/plain"
                invokeActionId: "bb.action.SHARE"
            }
            onTriggered: {
                data = "J'ai cherché une AutoLib' via l'application AutoLib' Paris pour Blackberry 10";
            }
        }
    ]
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
        remote: true    
            onDataLoaded: {
                dataModel.clear(); 
                    dataModel.insertList(data.records);
                        myIndicator.visible = false;
                            }
                        } 
                ] 

    } 
    onCreationCompleted: {
        myIndicator.start();
        myIndicator.visible = false;
        }
}
