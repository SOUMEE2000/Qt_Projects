#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString FileName= QFileDialog::getOpenFileName(this, "Open the file: ");
    QFile file(FileName);
    currentFile = FileName;
    if(!file.open(QIODevice::ReadOnly | QFile:: Text))
    {
        QMessageBox::warning(this, "Warning","Warning: Cannot open file" + file.errorString());
        return;
    }
    setWindowTitle(FileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QString FileName= QFileDialog::getSaveFileName(this, "Save the file: ");
    QFile file(FileName);
    currentFile = FileName;
    if(!file.open(QFile:: WriteOnly | QFile:: Text))
    {
        QMessageBox::warning(this, "Warning","Warning: Cannot save file" + file.errorString());
        return;
    }
    setWindowTitle(FileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.close();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication :: quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

