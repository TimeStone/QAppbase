#ifndef CMDARGS_H
#define CMDARGS_H

#include "global.h"
#include <QObject>
#include <QCommandLineParser>
#include <QStringList>


class CmdArgs : public QObject
{
    Q_OBJECT

    DECLARE_SINGLETON(CmdArgs)


public:
    explicit CmdArgs(QObject *parent = nullptr);
    CmdArgs *cmdArgs;
    QStringList flashSequenceBoot;
    QStringList flashSequenceNormal;
    QString appText = "flash a device";
    QCommandLineParser allParser;
    QList<QCommandLineOption> alloptions;
    QCommandLineOption debugOption = QCommandLineOption(
                            QStringList() << "d" << "debug",
                            QCoreApplication::translate("main", "show more debug trace information"));

    QCommandLineOption portOption = QCommandLineOption(
                            QStringList() << "p" << "port",
                            QCoreApplication::translate("main", "Serial port name, default COM3"),
                            QCoreApplication::translate("main", "port"),
                            "COM3");

    QCommandLineOption baudrateOption = QCommandLineOption(
                            QStringList() << "b" << "baudrate",
                            QCoreApplication::translate("main", "Serial port baudrate, default 115200"),
                            QCoreApplication::translate("main", "baudrate"),
                            "115200");

    QCommandLineOption timeoutOption = QCommandLineOption(
                            QStringList() << "o" << "timeout",
                            QCoreApplication::translate("main", "flash timeout, default 30s"),
                            QCoreApplication::translate("main", "timeout"),
                            "30");

    QCommandLineOption typeOption = QCommandLineOption(
                            QStringList() << "t" << "type",
                            QCoreApplication::translate("main", "type of image to flash, such as bootloader, bootrom, mcu, etc"),
                            QCoreApplication::translate("main", "type"));

    QCommandLineOption fileOption = QCommandLineOption(
                            QStringList() << "i" << "image",
                            QCoreApplication::translate("main", "path of image to flash, such as xx.img, xx.bin, etc"),
                            QCoreApplication::translate("main", "image"));



signals:

public slots:
};

#define CMDARGS CmdArgs::getInstance()
#endif // CMDARGS_H
