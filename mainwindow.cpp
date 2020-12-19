#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CheckUi()
{
    if(ui->keyInput->text()!="" && ui->victoriesInput->text()!="")
        ui->addEntry->setEnabled(true);
    else
        ui->addEntry->setEnabled(false);

    if(_hash.getSize()<3)
        ui->findBest->setEnabled(false);
    else
        ui->findBest->setEnabled(true);
    if(_hash.getSize()==0)
    {
        ui->remove->setEnabled(false);
        ui->clear->setEnabled(false);
    }
    else
    {
        ui->remove->setEnabled(true);
        ui->clear->setEnabled(true);
    }
    if(ui->removeKey->text()=="")
        ui->remove->setEnabled(false);
}

void MainWindow::on_keyInput_textChanged(const QString &arg1)
{
    CheckUi();
}

void MainWindow::on_victoriesInput_textChanged(const QString &arg1)
{
    CheckUi();
}

void MainWindow::on_addEntry_clicked()
{
    bool ok;
    int victories = ui->victoriesInput->text().toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,"Wrong input", "Victories is not a number");
        return;
    }
    else
    {
        _hash.insert(ui->keyInput->text().toUtf8().constData(),victories);
        ui->keyInput->setText("");
        ui->victoriesInput->setText("");
        UpdateTable();
    }
    CheckUi();
}

void MainWindow::on_remove_clicked()
{
    _hash.remove(ui->removeKey->text().toUtf8().constData());
    ui->removeKey->setText("");
    CheckUi();
    UpdateTable();
}

void MainWindow::UpdateTable()
{
    QStringList headers;
    headers << "Student"<<"Victories";

    auto table=ui->tableWidget;
    table->clear();
    table->setRowCount(0);
    table->setHorizontalHeaderLabels(headers);
    _hash.printToTable(table);
}

void MainWindow::on_removeKey_textChanged(const QString &arg1)
{
    CheckUi();
}

void MainWindow::on_clear_clicked()
{
    _hash.clear();
    UpdateTable();
    CheckUi();
}

void MainWindow::on_findBest_clicked()
{
    _hash.findBest(ui->bestLabel);
}
