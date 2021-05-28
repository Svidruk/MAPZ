#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "botinterface.h"
#include "botprototypes.h"
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CreateBot_clicked();

    void on_RunBot_clicked();

private:
    Ui::MainWindow *ui;
    QVector<BotPrototype*> Bots;
    int ids = 0;
    BotStorage *BS;
};

#endif // MAINWINDOW_H
