#ifndef HOUSEDIALOG_H
#define HOUSEDIALOG_H
#include <QDialog>
#include "storehouse.h"
#include <QGraphicsRectItem>
namespace Ui {
    class housedialog;
}

class housedialog : public QDialog
{
    Q_OBJECT

public:
    explicit housedialog(QGraphicsRectItem *curItem,QWidget *parent = 0);
    ~housedialog();
    storehouse now;
    void accept();
private slots:

protected:
    Ui::housedialog *ui;
private slots:
    void onAccepted();
    void on_housedialog_accepted();
    void on_buttonBox_accepted();
};

#endif // HOUSEDIALOG_H
