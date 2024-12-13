#include "mainwindow.h"
#include "qboxlayout.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout(ui->centralwidget);  // 创建一个垂直布局
    treeview = new TreeView(this);
    layout->addWidget(treeview);  // 将按钮添加到布局中
}

MainWindow::~MainWindow()
{
    delete ui;
}
