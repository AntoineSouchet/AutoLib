#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
        namespace maps
        {
            class MapView;
        }
    }
    namespace platform
    {
        namespace geo
        {
            class GeoLocation;
        }
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }
    Q_INVOKABLE void addPinAtCurrentMapCenter();

private slots:
    void onSystemLanguageChanged();
private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    bb::cascades::maps::MapView* mapView;
    bb::platform::geo::GeoLocation* deviceLocation;
};

#endif /* ApplicationUI_HPP_ */
