#include "shelfdialog.h"
#include "ui_shelfdialog.h"
#include <qmessagebox.h>
//本文件主要用于仓库界面的操作实现

//构造函数
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
    if( onAccepted() )
		QDialog::accept();
}
//将输入的信息储存到shelfdialog类中的storehouse类中
bool shelfdialog::onAccepted()
{
    now.name=ui->nameEdit->text();
    now.y=ui->xEdit->text().toInt();
    now.z=ui->yEdit->text().toInt();
	if( ui->xEdit->text().toInt() <=0 || ui->yEdit->text().toInt() <= 0 )//判断是否有非法输入
	{
		QMessageBox::about(NULL, "Warning", "Exist <font color = 'red'> ILLEGAL </font>input, please input again!" );
		return false;
	}

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
	return true;
}
