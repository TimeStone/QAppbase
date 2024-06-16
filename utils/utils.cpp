#include "utils.h"
#include <QTextStream>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

void Utils::consolePrint(QString msg, bool isError=false){
    if(isError){
        QTextStream(stdout) << msg << endl;
    }else{
        QTextStream(stderr) << msg << endl;
    }
};
