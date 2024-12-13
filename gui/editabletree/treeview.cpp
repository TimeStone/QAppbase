#include "treeview.h"
#include "addnodedlg.h"
#include "jsontreemodel.h"
#include "qsettings.h"
#include "ui_treeview.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>

TreeView::TreeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeView),
    newInsertText(tr("Insert new data")),
    treeViewColumnKey(tr("Node")),
    treeViewColumnValue(tr("Value")),
    treeViewColumnType(tr("Type"))
{
    ui->setupUi(this);
    QString initData = "{\"users\":\"Ada\"}";
    ui->code->setPlainText(initData);
}

TreeView::~TreeView()
{
    delete ui;
}

void TreeView::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void TreeView::on_udateCode_pressed()
{
    formatCode();
}

void TreeView::on_updateTree_pressed()
{
    refreshJsonTree();
}


void TreeView::refreshJsonTree()
{
    if (!ui->code->document()->isEmpty())
    {
        QByteArray ss = ui->code->toPlainText().toLocal8Bit();
        std::string json = ui->code->toPlainText().toStdString();
        Json::Reader jsonReader;
        jsonValue.clear();
        jsonReader.parse(ss.data(), jsonValue);

        QStringList headers;
        headers << treeViewColumnKey << treeViewColumnValue << treeViewColumnType;



        QAbstractItemModel *oldModel = ui->tree->model();
        if (oldModel != NULL)
            oldModel->disconnect(SIGNAL(dataChanged(QModelIndex,QModelIndex)));

        JsonTreeModel *model = new JsonTreeModel(headers, jsonValue);
        QItemSelectionModel *selectionModel = ui->tree->selectionModel();
        connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(treeViewDataChanged()));
        ui->tree->setModel(model);
        ui->tree->reset();
        delete selectionModel;
        delete oldModel;


        ui->tree->expandAll();

        for (int i = 0; i < ui->tree->model()->columnCount(); i++)
            ui->tree->resizeColumnToContents(i);
    }
}

void TreeView::insertTreeNode()
{
    AddNodeDlg dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        if(ui->tree->selectionModel() == 0)
        {
            QMessageBox::warning(this,this->windowTitle(),"Adding a node to an empty tree is not supported.");
            return;
        }

        QModelIndex index = ui->tree->selectionModel()->currentIndex();
        QAbstractItemModel *model = ui->tree->model();

        if (!model->insertRow(index.row()+1, index.parent()))
            return;

        updateActions();

        /*
        for (int column = 0; column < model->columnCount(index.parent()); ++column)
        {
            QModelIndex child = model->index(index.row()+1, column, index.parent());
            model->setData(child, QVariant(newInsertText), Qt::EditRole);
        }
        */
        QModelIndex child = model->index(index.row()+1, 0, index.parent());
        model->setData(child, QVariant(dlg.getName()), Qt::EditRole);

        child = model->index(index.row()+1, 1, index.parent());
        model->setData(child, QVariant(dlg.getValue()), Qt::EditRole);

        child = model->index(index.row()+1, 2, index.parent());
        model->setData(child, QVariant(dlg.getType()), Qt::EditRole);
    }
}

void TreeView::insertTreeChild()
{
    AddNodeDlg dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        QModelIndex index = ui->tree->selectionModel()->currentIndex();
        JsonTreeModel *model = (JsonTreeModel*)ui->tree->model();

        if (index.column() != 0)
        {
            index = index.sibling(index.row(), 0);
        }

        if (model->columnCount(index) == 0)
        {
            if (!model->insertColumn(0, index))
                return;
        }

        if (!model->insertRow(0, index))
            return;

        /*
        for (int column = 0; column < model->columnCount(index); column++)
        {
            QModelIndex child = model->index(0, column, index);
            model->setData(child, QVariant(newInsertText), Qt::EditRole);
        }
        */

        QModelIndex child = model->index(0, 0, index);
        model->setData(child, QVariant(dlg.getName()), Qt::EditRole);

        child = model->index(0, 1, index);
        model->setData(child, QVariant(dlg.getValue()), Qt::EditRole);

        child = model->index(0, 2, index);
        model->setData(child, QVariant(dlg.getType()), Qt::EditRole);

        ui->tree->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                        QItemSelectionModel::ClearAndSelect);
        updateActions();
    }
}

void TreeView::deleteTreeNode()
{
    QModelIndex index = ui->tree->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->tree->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void TreeView::updateActions()
{
    bool hasSelection = !ui->tree->selectionModel()->selection().isEmpty();

    bool hasCurrent = ui->tree->selectionModel()->currentIndex().isValid();

}

void TreeView::treeViewDataChanged()
{
    for (int i = 0; i < ui->tree->model()->columnCount(); i++)
    {
        ui->tree->resizeColumnToContents(i);
        ui->tree->setColumnWidth(i, ui->tree->columnWidth(i) + 20);
    }
}

void TreeView::formatCode()
{
    if (ui->tree->model() != NULL)
    {
        ui->code->clear();

        QString codeText = "";
        JsonTreeModel *model;
        model = (JsonTreeModel*)ui->tree->model();
        codeText += treeFormat(model->getRootItem(), "", true);

        ui->code->setPlainText(codeText);
    }
}

QString TreeView::treeFormat(JsonTreeItem *treeItem, QString indent, bool noHeader)
{
    QString resultStr;
    QString objectKey = treeItem->data(0).toString();
    QString objectValue = treeItem->data(1).toString();
    QString objectType = treeItem->data(2).toString();

    if (noHeader)
    {
        resultStr = indent;
    }
    else
    {
        resultStr = indent + QString("\"") + objectKey + "\": ";
    }

    if (objectType.compare(tr("object"), Qt::CaseInsensitive) == 0
        || objectType.compare(treeViewColumnType, Qt::CaseInsensitive) == 0)
    {
        resultStr += "{\n";
        JsonTreeItem *subObjectItem;
        for (int i = 0; i < treeItem->childCount(); i++)
        {
            subObjectItem = treeItem->child(i);
            resultStr += treeFormat(subObjectItem, indent + "    ");
        }
        if(treeItem->childCount() > 0)
            resultStr.remove(resultStr.length() - 2, 1);// remove trailing comma
        resultStr += indent + "},\n";
    }
    else if (objectType.compare(tr("array"), Qt::CaseInsensitive) == 0)
    {
        resultStr += "[\n";
        JsonTreeItem *subObjectItem;
        for (int i = 0; i < treeItem->childCount(); i++)
        {
            subObjectItem = treeItem->child(i);
            resultStr += treeFormat(subObjectItem, indent + "    ", true);
        }
        if(treeItem->childCount() > 0)
            resultStr.remove(resultStr.length() - 2, 1);// remove trailing comma
        resultStr += indent + "],\n";
    }
    else
    {
        if (objectType.compare(tr("string"), Qt::CaseInsensitive) == 0 ||
            objectType.compare(newInsertText, Qt::CaseInsensitive) == 0)
        {
            resultStr += "\"" + objectValue + "\",\n";
        }
        else
        {
            resultStr += objectValue + ",\n";
        }
    }

    return resultStr;
}

void TreeView::showHelp()
{
    QMessageBox::information(this, tr("Using Help"), tr(
                                                         "1 On the left side of the main interface to fill the JSON code \n"
                                                         "2 Click on the menu \" Generate code tree \", the right of the main interface will spanning tree \n"
                                                         "3 To insert or delete after the tree node or modify the value, click on the menu \" Generate Code \", will generate JSON code from the tree."												  ));
}

//void TreeView::dataEdit(QModelIndex editIndex)
//{
//    QString vType = editIndex.sibling(editIndex.row(), 2).data(Qt::EditRole).toString();

//    if (vType.compare(tr("object")) != 0
//        && vType.compare(tr("array")) != 0)
//    {
//        if (editIndex.column() >= 2)
//        {
//            QModelIndex newIndex = editIndex.sibling(editIndex.row(), 1);
//            ui->tree->edit(newIndex);
//        }
//    }
//    else
//    {
//        QModelIndex newIndex = editIndex.sibling(editIndex.row(), 0);
//        ui->tree->edit(newIndex);
//    }
//}

void TreeView::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}

void TreeView::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void TreeView::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,"Open Json File",lastFilePath);
        if (!fileName.isEmpty())
        {
            QFileInfo info(fileName);
            lastFilePath = info.absoluteDir().absolutePath();
            loadFile(fileName);
        }
    }

    //refreshJsonTree();
}

bool TreeView::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool TreeView::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if (files.isEmpty())
        return false;

    return saveFile(files.at(0));
}

void TreeView::readSettings()
{
    QSettings settings;
    //    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    //    QSize size = settings.value("size", QSize(400, 400)).toSize();
    //    resize(size);
    //    move(pos);
    this->restoreGeometry(settings.value("geometry").toByteArray());
    lastFilePath = (settings.value("file_path").toString());
    curFile = settings.value("last_opened_file").toString();
    if(this->curFile.length() != 0)
    {
        loadFile(curFile);
        refreshJsonTree();
    }
}

void TreeView::writeSettings()
{
    QSettings settings;
    //    settings.setValue("pos", pos());
    //    settings.setValue("size", size());
    settings.setValue("geometry", this->saveGeometry());
    settings.setValue("file_path", lastFilePath);
    settings.setValue("last_opened_file", this->curFile);
}

bool TreeView::maybeSave()
{
    if (ui->code->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, this->windowTitle(),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void TreeView::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, this->windowTitle(),
                             tr("Cannot read file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);

}

bool TreeView::saveFile(const QString &fileName)
{
    formatCode();

    QFile file(fileName);
    QFileInfo info(fileName);
    lastFilePath = info.absoluteDir().absolutePath();
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, this->windowTitle(),
                             tr("Cannot write file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    //statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void TreeView::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    ui->code->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.json";
    setWindowFilePath(shownName);
}

QString TreeView::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void TreeView::on_addChild_pressed()
{
    insertTreeChild();
}


void TreeView::on_addNode_pressed()
{
    insertTreeNode();
}


void TreeView::on_delNode_pressed()
{
    deleteTreeNode();
}


void TreeView::on_addCol_pressed()
{

    QString Name = "newItem";
    QString Value = "ItemValue";
    QString Type = "timeType";
    QModelIndex index = ui->tree->selectionModel()->currentIndex();
    JsonTreeModel *model = (JsonTreeModel*)ui->tree->model();

    if (index.column() != 0)
    {
        index = index.sibling(index.row(), 0);
    }

    if (model->columnCount(index) == 0)
    {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    QModelIndex child = model->index(0, 0, index);
    model->setData(child, QVariant(Name), Qt::EditRole);

    child = model->index(0, 1, index);
    model->setData(child, QVariant(Value), Qt::EditRole);

    child = model->index(0, 2, index);
    model->setData(child, QVariant(Type), Qt::EditRole);

    ui->tree->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                QItemSelectionModel::ClearAndSelect);
    updateActions();
}


void TreeView::on_delCol_pressed()
{

}


