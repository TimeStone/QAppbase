#include "basicform.h"
#include "ui_basicform.h"
#include "utils/utils.h"
#include <QThread>

BasicForm::BasicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasicForm)
{
    ui->setupUi(this);
}

BasicForm::~BasicForm()
{
    delete ui;
}

void BasicForm::on_pushButton_pressed()
{
    Utils *utils = new Utils();
    ui->infoText->append("Will Hang and crash after 5 seconds");
    QThread::sleep(5);
    //utils->crashIt();
}
