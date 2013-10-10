#ifndef CONNECTDB_H
#define CONNECTDB_H
#include <QDialog>
namespace Ui {
	class connectdb;
}

class connectdb : public QDialog
{
	Q_OBJECT;

public:
	explicit connectdb(QWidget *parent = 0);
	~connectdb();
	void accept();
	
	QString label_1,label_2,label_3;

protected:
	Ui::connectdb *ui;

private slots:
	void onAccept();
};

#endif