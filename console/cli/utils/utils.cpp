#include "utils.h"
#include <QTextStream>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

void Utils::consoleP(QString msg, bool isError){
    if(isError){
        QTextStream(stderr) << msg << endl;
    }else{
        QTextStream(stdout) << msg << endl;
    }
};
