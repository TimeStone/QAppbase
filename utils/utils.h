#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    void static consolePrint(QString msg, bool isError);

signals:

public slots:
};

#endif // UTILS_H
