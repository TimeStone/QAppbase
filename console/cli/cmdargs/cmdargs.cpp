#include "cmdargs.h"
#include "global.h"

CmdArgs::CmdArgs(QObject *parent) : QObject(parent)
{

    allParser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    alloptions << debugOption
               << portOption
               << baudrateOption
               << timeoutOption
               << typeOption
               << fileOption;

    allParser.addOptions(alloptions);
}
