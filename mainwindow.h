#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <conhouse.h>
#include <conbill.h>
#include <conitem.h>
#include <conshelf.h>
#include <storescene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    storescene * scene;
    conhouse * house;
    conshelf * shelf;
    conitem * item;
    conbill * bill;
private slots:
    void on_massOutputButton_clicked();

    void on_pathButton_clicked();

    void on_finOutputButton_clicked();

    void on_initHouseButton_clicked();

    void on_initInputButton_clicked();

    void on_finInputButton_clicked();

    void on_massInputButton_clicked();

    void on_initOutputButton_clicked();

    void on_searchButton_clicked();

    void get_items_of_shelf(int);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
