#include "housedialog.h"
#include "ui_housedialog.h"
//#include <QDebug>

housedialog::housedialog(QGraphicsRectItem *curItem ,QWidget *parent):
    QDialog(parent),
    ui(new Ui::housedialog)
{
    ui->setupUi(this);
    now.figure=curItem;
}

housedialog::~housedialog(){
    delete ui;
}

void housedialog::accept()
{
    //qDebug()<<"!!!!";
    onAccepted();
    QDialog::accept();
}

void housedialog::onAccepted()
{
    now.name=ui->nameEdit->text();
    QRect rect=now.figure->rect().toRect();
    now.x=rect.x()+ rect.width()*(ui->xposEdit->text().toDouble()/ui->widthEdit->text().toDouble() );
    now.y=rect.y()+ rect.height()*(ui->yposEdit->text().toDouble()/ui->heightEdit->text().toDouble());
    now.description=ui->desEdit->document()->toPlainText();
    //qDebug()<<now.x<<","<<now.y;
}

void housedialog::on_housedialog_accepted()
{
    //qDebug()<<"2";
    onAccepted();
    QDialog::accept();
}

void housedialog::on_buttonBox_accepted()
{
    //qDebug()<<"1";
    on_housedialog_accepted();
}
