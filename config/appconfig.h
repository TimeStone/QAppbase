#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include "core/global.h"

typedef struct ConfigMap{
    QString AppName = "BaseMap";
    QString AppImage = "BaseMap.png";
    QString css = "BaseApp.css";
}CMAP;

class AppConfig : public QObject
{
    Q_OBJECT
    DECLARE_SINGLETON(AppConfig)

public:
    AppConfig();
};

#define APPCONFIG AppConfig::getInstance()

#endif // APPCONFIG_H
