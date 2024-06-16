#include "listcmd.h"
#include "utils/utils.h"
#include <QTextStream>
#include <QCoreApplication>
#include <QSerialPortInfo>

ListCMD::ListCMD(QObject *parent) : QObject(parent)
{

}
void ListCMD::listDevices(){
    const auto ports = QSerialPortInfo::availablePorts();
    if(ports.isEmpty()){
        Utils::consoleP("No serial port found");
        QCoreApplication::exit(0);
    }else{
        Utils::consoleP(QString("Total %1 avaliable ports:").arg(ports.size()));
        for(const QSerialPortInfo &port : ports){
            QTextStream(stdout) << "port; " << port.portName()
                                << ", Description: " << port.description()
                                << ", Manufacturer: " << port.manufacturer()
                                << endl;

        }
    }
};
