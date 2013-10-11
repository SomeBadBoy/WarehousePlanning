#include "dbms.h"
#include <qmessagebox.h>
extern char username[20],password[20],dbname[20];
DBMS::DBMS(){
    this->initialize_sql();
    this->connect_sql();
}

DBMS::~DBMS(){
    this->disconnet_sql();
}

int DBMS::initialize_sql(){
    return mysql_init(&mysql_conn)?0:1;
}

int DBMS::connect_sql(){
	flag = mysql_real_connect(&mysql_conn, "localhost", username, password,
			dbname, MYSQL_PORT, NULL, 0);
	if ( !flag )//修复了未正确连接数据库也会打开软件的BUG
	{
		QMessageBox::about(NULL,"error","Failed to connect to mysql!");
		exit(-2);
//	return mysql_real_connect(&mysql_conn, "localhost", username, password,
//			dbname, MYSQL_PORT, NULL, 0)?0:1;
	}
	return 0;
}

int DBMS::disconnet_sql(){
     mysql_close(&mysql_conn);
     return 0;
}

int DBMS::end_server_sql(){
    mysql_server_end();
    return 0;
}

int DBMS::query(char *sqlcmd){
    return mysql_query(&mysql_conn, sqlcmd)==0?0:1;
}

