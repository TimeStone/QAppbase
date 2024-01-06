#ifndef APPBASE_H
#define APPBASE_H

#include <QObject>
#include "global.h"
#include "config/appconfig.h"
class AppBase : public QObject
{
    Q_OBJECT

    //DECLARE_SINGLETON(SQLiteStudio)
public:
    AppConfig *appConfig;
    AppBase();
};

#define APPBASE AppBase::getInstance()

#endif // RUNTIME_H
