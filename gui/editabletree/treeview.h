#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "jsonc/jsoncxx.h"
#include "jsontreeitem.h"
#include <QWidget>
#include <QTextEdit>

namespace Ui {
class TreeView;
}

class TreeView : public QWidget
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = nullptr);
    ~TreeView();

private slots:
    void on_udateCode_pressed();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    Ui::TreeView *ui; 
    Json::Value jsonValue;

    const QString newInsertText;
    const QString treeViewColumnKey;
    const QString treeViewColumnValue;
    const QString treeViewColumnType;

    QString treeFormat(JsonTreeItem* treeItem = NULL, QString indent = "", bool noHeader = false);
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString curFile;
    QTextEdit *textEdit;
    QString lastFilePath;

private slots:
    void refreshJsonTree();
    void insertTreeNode();
    void deleteTreeNode();
    void insertTreeChild();
    void updateActions();
    void treeViewDataChanged();
    void formatCode();
    void showHelp();
    //void dataEdit(QModelIndex editIndex);
    void open();
    bool save();
    bool saveAs();
    void documentWasModified();

    void on_updateTree_pressed();
    void on_addNode_pressed();
    void on_delNode_pressed();
    void on_addCol_pressed();
    void on_delCol_pressed();
    void on_addChild_pressed();
};

#endif // TREEVIEW_H
