#include "historytree.h"
#include "ui_historytree.h"
#include <QDebug>
#include "gui/basic/basicform.h"

HistoryTree::HistoryTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryTree)
{
    ui->setupUi(this);
    ui->plainTextEdit->appendPlainText("history tree loaded");

}

void HistoryTree::addText(){
    //qDebug() << "try add text";
    BASICFORM->appendText("Hello hoyo works");
    BASICFORM->infoText->append("History Tree already loaded!");
}
HistoryTree::~HistoryTree()
{
    delete ui;
}

void HistoryTree::on_pushButton_pressed()
{
    //qDebug() << "try add text";
    BASICFORM->appendText("Hello GLOBAL SINGLETON works");
    BASICFORM->infoText->append("aaa");
}
