#include "dbms.h"

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
    return mysql_real_connect(&mysql_conn, "localhost", "root","mysql",
                              "store", MYSQL_PORT, NULL, 0)?0:1;
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

