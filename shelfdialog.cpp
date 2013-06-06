#include "shelfdialog.h"
#include "ui_shelfdialog.h"


shelfdialog::shelfdialog(QGraphicsRectItem *curItem ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shelfdialog)
{
    ui->setupUi(this);
    now.figure=curItem;
}

shelfdialog::~shelfdialog(){
    delete ui;
}

void shelfdialog::accept()
{
    onAccepted();
    QDialog::accept();
}

void shelfdialog::onAccepted()
{
    now.name=ui->nameEdit->text();
    now.y=ui->xEdit->text().toInt();
    now.z=ui->yEdit->text().toInt();

    switch (ui->typeBox->currentIndex()){
    case (0):
        now.x=0;
        now.thin=2;
        break;
    case (1):
        now.x=2;
        now.thin=2;
        break;
    case (2):
        now.x=0;
        now.thin=1;
        break;
    case (3):
        now.x=1;
        now.thin=1;
        break;
    case (4):
        now.x=2;
        now.thin=1;
        break;
    case (5):
        now.x=3;
        now.thin=1;
        break;
    }
    now.description=ui->desEdit->document()->toPlainText();

}
