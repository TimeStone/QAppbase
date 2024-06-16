#ifndef LISTCMD_H
#define LISTCMD_H

#include <QObject>

class ListCMD : public QObject
{
    Q_OBJECT
public:
    explicit ListCMD(QObject *parent = nullptr);
    static void listDevices();
signals:

public slots:
};

#endif // LISTCMD_H
