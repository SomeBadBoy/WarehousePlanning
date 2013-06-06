#ifndef SHELFDIALOG_H
#define SHELFDIALOG_H
#include <QDialog>
#include <QGraphicsRectItem>
#include <storeshelf.h>
namespace Ui {
    class shelfdialog;
}

class shelfdialog : public QDialog
{
    Q_OBJECT
public:
    explicit shelfdialog(QGraphicsRectItem *curItem,QWidget *parent = 0);
    ~shelfdialog();
    void accept();
    storeshelf now;
signals:
    
public slots:
protected:
    Ui::shelfdialog *ui;
private slots:
    void onAccepted();
};

#endif // SHELFDIALOG_H
