#ifndef APPLOGHANDLER_H
#define APPLOGHANDLER_H

#include <QObject>
#include <QTextStream>

class Apploghandler : public QObject
{
    Q_OBJECT
public:
    explicit Apploghandler(QObject *parent = nullptr);
    ~Apploghandler();
    static void handleColorMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void handlePlainMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void setType(int logType);
    static QString getColorCode(QtMsgType type);
private:
    static QTextStream out;
};

#endif // APPLOGHANDLER_H
