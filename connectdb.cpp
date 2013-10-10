#include "connectdb.h"
#include "ui_connectdb.h"
char username[20],password[20],dbname[20];
connectdb::connectdb(QWidget *parent):
	ui(new Ui::connectdb)
{
	ui->setupUi(this);
}

connectdb::~connectdb()
{
	delete ui;
}

void connectdb::accept()
{

	onAccept();
	QDialog::accept();
}

void connectdb::onAccept()
{
	label_1 = ui->username->text();
	strcpy(username, label_1.toAscii());
	label_2 = ui->password->text();
	strcpy(password, label_2.toAscii());
	label_3 = ui->dbname->text();
	strcpy(dbname, label_3.toAscii());
}