#include "apploghandler.h"
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QLoggingCategory>
#include <QMessageLogContext>
#include <QFile>

Apploghandler::Apploghandler(QObject *parent) : QObject(parent)
{

}

Apploghandler::~Apploghandler(){
    qInstallMessageHandler(0);
}

void Apploghandler::handleColorMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
//    QString ts = currentDateTime.toString(Qt::ISODate);
//    QString file = QString(context.file);
//    QString function = QString(context.function);
    QString colorCode = getColorCode(type);

    QString cleanMSG;
    if(msg.startsWith('"') &&  msg.endsWith('"')){
        cleanMSG = msg.mid(1, msg.length()-2);
    }else{
        cleanMSG = msg;
    }
    switch(type){
    case QtDebugMsg:
        out << colorCode << "[debug]" << cleanMSG << "\033[0m" << "\n";
        break;
    case QtInfoMsg:
        out << colorCode << "[info]" << cleanMSG << "\n";
        break;
    case QtWarningMsg:
        out << colorCode << "[status]" << cleanMSG << "\033[0m" << "\n";
        break;
    case QtCriticalMsg:
        out << colorCode << "[error]" << cleanMSG << "\033[0m" << "\n";
        break;
    case QtFatalMsg:
        out << colorCode << "[fatal]" << cleanMSG << "\033[0m" << "\n";
        break;
    default:
        out << colorCode << "[info]" << cleanMSG << "\033[0m" << "\n";
        break;
    }
    out.flush();
}

void Apploghandler::handlePlainMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg){
//    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
//    QString ts = currentDateTime.toString(Qt::ISODate);
//    QString file = QString(context.file);
//    QString function = QString(context.function);
    QString colorCode = getColorCode(type);

    QString cleanMSG;
    if(msg.startsWith('"') &&  msg.endsWith('"')){
        cleanMSG = msg.mid(1, msg.length()-2);
    }else{
        cleanMSG = msg;
    }
    switch(type){
    case QtDebugMsg:
        out << colorCode << "[debug]" << cleanMSG << "\n";
        break;
    case QtInfoMsg:
        out << colorCode << "[info]" << cleanMSG << "\n";
        break;
    case QtWarningMsg:
        out << colorCode << "[status]" << cleanMSG << "\n";
        break;
    case QtCriticalMsg:
        out << colorCode << "[error]" << cleanMSG << "\n";
        break;
    case QtFatalMsg:
        out << colorCode << "[fatal]" << cleanMSG << "\n";
        break;
    default:
        out << colorCode << "[info]" << cleanMSG <<  "\n";
        break;
    }
    out.flush();
}

void Apploghandler::setType(int logType){
    if(logType == 0){
        qInstallMessageHandler(handlePlainMessage);
    }else if(logType == 1){
        qInstallMessageHandler(handleColorMessage);
    }else if(logType == 2){
        qInstallMessageHandler(0);
    }else{
        qInstallMessageHandler(0);
    }
}

QString Apploghandler::getColorCode(QtMsgType type){
    switch(type){
    case QtDebugMsg:
        return "\033[0;37m";
    case QtInfoMsg:
        return "\033[0;38m";
    case QtWarningMsg:
        return "\033[0;38m";
    case QtCriticalMsg:
        return "\033[0;31m";
    case QtFatalMsg:
        return "\033[0;31m";
    default:
        return "\033[0m";
    }
}
