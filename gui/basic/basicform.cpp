#include "basicform.h"
#include "ui_basicform.h"
#include "gui/historytree/historytree.h"
#include "utils/utils.h"
#include <QMessageBox>
#include <QThread>
#include <QDebug>

DEFINE_SINGLETON(BasicForm)

BasicForm::BasicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasicForm)
{
    ui->setupUi(this);
    //ui->tab2->
    HistoryTree * historyTreeTab = new HistoryTree;
    //ui->
    ui->tabWidget->addTab(historyTreeTab, "historyTree");
    infoText = ui->infoText;
    infoText->append("BasicForm Loaded");
}

BasicForm::~BasicForm()
{
    delete ui;
}


void BasicForm::appendText(QString text)
{
    qDebug() << "Yes I got the message" << text;
    ui->infoText->append(text);
}

void BasicForm::on_pushButton_pressed()
{
    Utils *utils = new Utils();
    ui->infoText->append("Will Hang and crash after 5 seconds");
    QThread::sleep(5);
    //utils->crashIt();
}


void BasicForm::on_messageButton_pressed()
{
    QMessageBox::information(this, "information", "this is the information example");
}
