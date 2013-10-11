#include "housedialog.h"
#include "ui_housedialog.h"
#include <qmessagebox.h>
#include <QDebug>
///���ļ���Ҫ���ڲֿ����Ĳ���ʵ��

//���캯��
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

void housedialog::reject()//�޸�cancel����Чbug
{
//	if(!QMessageBox::information(this,"Warning","Exit will lose any unsaved data, whether to quit",
//		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes ))
//		this->close();
//	else
		QDialog::reject();
}

void housedialog::accept()
{
    //qDebug()<<"!!!!";
    onAccepted();
    QDialog::accept();
}
//���������Ϣ���浽housedialog����
bool housedialog::onAccepted()
{
    now.name=ui->nameEdit->text();
    QRect rect=now.figure->rect().toRect();
	if( ui->xposEdit->text().toDouble() <=0 || ui->yposEdit->text().toDouble() <=0 ||
		ui->widthEdit->text().toDouble() <=0 || ui->heightEdit->text().toDouble() <=0 )
	{
		QMessageBox::about(NULL,"Warning","Exist <font color = 'red'> ILLEGAL </font> input! Please input again.");
		return false;
	}

    now.x=rect.x()+ rect.width()*(ui->xposEdit->text().toDouble()/ui->widthEdit->text().toDouble() );
    now.y=rect.y()+ rect.height()*(ui->yposEdit->text().toDouble()/ui->heightEdit->text().toDouble());
    now.description=ui->desEdit->document()->toPlainText();
	return true;
    //qDebug()<<now.x<<","<<now.y;
}

void housedialog::on_housedialog_accepted()
{
    //qDebug()<<"2";
    if( onAccepted() )//����ж��Ƿ��зǷ����룬�����˻�����
		QDialog::accept();
}

void housedialog::on_buttonBox_accepted()
{
    //qDebug()<<"1";
    on_housedialog_accepted();
}
