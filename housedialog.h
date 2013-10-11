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
	void reject();
protected:
    Ui::housedialog *ui;
private slots:
    bool onAccepted();
    void on_housedialog_accepted();
    void on_buttonBox_accepted();
//	void onRejected();
};

#endif // HOUSEDIALOG_H
