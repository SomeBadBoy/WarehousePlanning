#include "housedialog.h"
#include "ui_housedialog.h"
#include <qmessagebox.h>
#include <QDebug>

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
void housedialog::reject()//修复cancel键无效bug
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
    if( onAccepted() )//添加判断是否有非法输入，有则退回重输
		QDialog::accept();
}

void housedialog::on_buttonBox_accepted()
{
    //qDebug()<<"1";
    on_housedialog_accepted();
}
