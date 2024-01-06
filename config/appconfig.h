#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>

typedef struct ConfigMap{
    QString AppName = "BaseMap";
    QString AppImage = "BaseMap.png";
    QString css = "BaseApp.css";
}CMAP;

class AppConfig
{
public:
    AppConfig();
};

#endif // APPCONFIG_H
