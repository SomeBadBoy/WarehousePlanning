#include "conhouse.h"

conhouse::conhouse()
{
    house.id=-1;
    char cmd[400];
    sprintf(cmd,"select * from house");
    if (query(cmd)==0){
        storehouse tmp;
        mysql_result=mysql_store_result(&mysql_conn);
        if((mysql_row=mysql_fetch_row(mysql_result))){
            tmp.id=atoi(mysql_row[0]);
            tmp.name=QString(QLatin1String(mysql_row[1]));
            tmp.figure=new QGraphicsRectItem;
            tmp.figure->setRect(atoi(mysql_row[2]),atoi(mysql_row[3]),atoi(mysql_row[4]),atoi(mysql_row[5]));
            tmp.description=QString(QLatin1String(mysql_row[6]));
            house=tmp;
        }
        //qDebug()<<house.id<<endl;
    }
}

void conhouse::insert_house(storehouse& u){
    if (house.id>0)return ;
    char cmd[400];
    sprintf(cmd,"insert into house(name,x,y,w,h,description) values(\'%s\',%d,%d,%d,%d,\'%s\')",
            u.name.toLatin1().data(),u.figure->rect().toRect().x(),u.figure->rect().toRect().y(),
            u.figure->rect().toRect().width(),u.figure->rect().toRect().height(),u.description.toLatin1().data()
            );
    query(cmd);
    sprintf(cmd,"select LAST_INSERT_ID()");
    query(cmd);
    mysql_result=mysql_store_result(&mysql_conn);
    mysql_row=mysql_fetch_row(mysql_result);
    u.id=QString(QLatin1String(mysql_row[0])).toInt();
    house=u;
    return ;
}

void conhouse::delete_house(){
    if (house.id<0)return;
    char cmd[400];
    delete house.figure;
    sprintf(cmd,"delete from house where house.id=%d",house.id);
    house.id=-1;
    query(cmd);
    return ;
}
