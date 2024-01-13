#ifndef HISTORYTREE_H
#define HISTORYTREE_H

#include <QWidget>

namespace Ui {
class HistoryTree;
}

class HistoryTree : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryTree(QWidget *parent = nullptr);
    void addText();
    ~HistoryTree();

private slots:
    void on_pushButton_pressed();

private:
    Ui::HistoryTree *ui;
};

#endif // HISTORYTREE_H
