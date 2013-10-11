#include "conshelf.h"

conshelf::conshelf()
{
    char cmd[400];
    view.clear();
    sprintf(cmd,"select * from shelf");

    if (query(cmd)==0){
        storeshelf tmp;
        mysql_result=mysql_store_result(&mysql_conn);
        while ((mysql_row=mysql_fetch_row(mysql_result))){
            tmp.id=atoi(mysql_row[0]);
            tmp.name=QString(QLatin1String(mysql_row[1]));
            tmp.belong_to=atoi(mysql_row[2]);
            tmp.figure=new QGraphicsRectItem;
            tmp.figure->setRect(atoi(mysql_row[3]),atoi(mysql_row[4]),atoi(mysql_row[5]),atoi(mysql_row[6]));
            tmp.x=atoi(mysql_row[7]);
            tmp.y=atoi(mysql_row[8]);
            tmp.z=atoi(mysql_row[9]);
            tmp.thin=atoi(mysql_row[10]);
            tmp.description=QString(QLatin1String(mysql_row[11]));
            view[tmp.id]=tmp;
        }
    }
}

void conshelf::insert_shelf(storeshelf &u){
    char cmd[400];
    sprintf(cmd,"insert into shelf(name,belong_to,x,y,w,h,direc,col,layer,thin,description)values(\'%s\',%d,%d,%d,%d,%d,%d,%d,%d,%d,\'%s\')",
            u.name.toLatin1().data(),u.belong_to,u.figure->rect().toRect().x(),u.figure->rect().toRect().y(),u.figure->rect().toRect().width(),
            u.figure->rect().toRect().height(),u.x,u.y,u.z,u.thin,u.description.toLatin1().data()
            );
    query(cmd);
    sprintf(cmd,"select LAST_INSERT_ID()");
    query(cmd);
    mysql_result=mysql_store_result(&mysql_conn);
    mysql_row=mysql_fetch_row(mysql_result);
    u.id=QString(QLatin1String(mysql_row[0])).toInt();
    view[u.id]=u;
    return ;
}

void conshelf::delete_shelf(int ID){
    char cmd[400];

    sprintf(cmd,"delete from shelf where shelf.id=%d",ID);
    delete view[ID].figure;
    view.erase(view.find(ID));
    query(cmd);
    return ;
}
Node conshelf::toNode(const storeitem & u,int id)
{
    QRect shelf=view[u.belong_to].figure->rect().toRect();
    QPoint p;
    double y=view[u.belong_to].y;
    //qDebug()<<"#"<<shelf.x()<<shelf.y()<<shelf.right()<<shelf.bottom()<<u.y<<y;
    switch (u.x){
    case(0):
        p=shelf.topRight();
        p.rx()-=(u.y/y)*shelf.width();
        p.ry()-=3;
        break;
    case(1):
        p=shelf.bottomLeft();
        p.rx()+=(u.y/y)*shelf.width();
        p.ry()+=3;
        break;
    case(2):
        p=shelf.topLeft();
        p.rx()-=3;
        p.ry()+=(u.y/y)*shelf.height();
        break;
    case(3):
        p=shelf.bottomRight();
        p.rx()+=3;
        p.ry()-=(u.y/y)*shelf.height();
        break;
    }
    return Node(p.x(),p.y(),id);
}
