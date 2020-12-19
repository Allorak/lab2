#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <hashtable.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_keyInput_textChanged(const QString &arg1);

    void on_victoriesInput_textChanged(const QString &arg1);

    void on_addEntry_clicked();

    void on_remove_clicked();

    void on_removeKey_textChanged(const QString &arg1);

    void on_clear_clicked();

    void on_findBest_clicked();

private:
    Ui::MainWindow *ui;
    void CheckUi();
    HashMap<string> _hash;
    void UpdateTable();
};
#endif // MAINWINDOW_H
