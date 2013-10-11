#ifndef DBMS_H
#define DBMS_H

#ifndef __LCC__
#define __LCC__
#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <QString>
#include <mysql.h>
//#include <QDebug>

class DBMS
{
public:
	DBMS();
    ~DBMS();
    int initialize_sql();
    int connect_sql();
    int disconnet_sql();
    int end_server_sql();
    int query(char *sqlcmd);
    int errorCode;

protected:
    MYSQL_RES *mysql_result;
    MYSQL_ROW mysql_row;
    MYSQL mysql_conn;
	MYSQL * flag;
private:
    //int errorCode;
};

#endif // DBMS_H
