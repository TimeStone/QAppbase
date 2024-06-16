
#include "cmdargs/cmdargs.h"
#include "utils/utils.h"
#include "functions/listcmd.h"
#include <QCoreApplication>
#include <QTranslator>
#include <QDir>
#include <QDebug>
#include <QCommandLineParser>



int main(int argc, char *argv[])
{
    QString appName = "Download Tool";
    QString appVersion = "0.1.0";
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(appName);
    QCoreApplication::setApplicationVersion(appVersion);
    QStringList args = QCoreApplication::arguments();

    CmdArgs cmdArgs;
    QCommandLineParser parser;
    parser.addPositionalArgument("subcommand", "actions to execute (flash, read, write, list)");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions(cmdArgs.alloptions);
    parser.process(args);

    if(args.length() < 2){
        Utils::consoleP("[error] please provide subcommand: flash, read, write, list, and then options");
        parser.showHelp(-1);
    }

//    if(!parser.isSet(cmdArgs.typeOption)){
//        Utils::consoleP("[error] type options is required!");
//        parser.showHelp(-1);
//    }

    QString appPath = QCoreApplication::applicationFilePath();
    QString currentPath = QDir::currentPath();
    Utils::consoleP("Tool path: " + appPath);
    Utils::consoleP("Current path: " + currentPath);

    QString subcommand = args[1];
    QStringList subargs = args.mid(1, -1);
    Utils::consoleP("sub function: " + subcommand);
    Utils::consoleP("sub options: " + subargs.join(" "));

    if(subcommand == "list"){
        ListCMD listCMD;
        listCMD.listDevices();
        QCoreApplication::exit(0);
    }else if (subcommand == "flash"){

    }else if (subcommand == "read"){

    }else if (subcommand == "write"){

    }else{
    }
    QCoreApplication::exit(0);
    return app.exec();
}
