#ifndef BASICFORM_H
#define BASICFORM_H

#include "core/global.h"
#include <QTextBrowser>
#include <QWidget>

namespace Ui {
class BasicForm;
}

class BasicForm : public QWidget
{
    Q_OBJECT
    DECLARE_SINGLETON(BasicForm)

public:

    QTextBrowser * infoText;
    Ui::BasicForm *ui;
    ~BasicForm();
    void appendText(QString text);

private:
    explicit BasicForm(QWidget *parent = nullptr);

private slots:
    void on_pushButton_pressed();

    void on_messageButton_pressed();

private:

};

#define BASICFORM BasicForm::getInstance()
#endif // BASICFORM_H
