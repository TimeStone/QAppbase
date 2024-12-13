#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <treeview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TreeView *treeview = nullptr;

};

#endif // MAINWINDOW_H
