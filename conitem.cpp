#include "conitem.h"

//构造函数，将数据库中货物的所有信息全部取出来，放在conitem类的QMap型数据view中，
//其中view是货物id与storeitem类对应。
conitem::conitem()
{
    char cmd[600];
    sprintf(cmd,"select * from item");
    QVector<storeitem> ret;
    view.clear();
    if (query(cmd)==0){
        storeitem tmp;
        mysql_result=mysql_store_result(&mysql_conn);
        while ((mysql_row=mysql_fetch_row(mysql_result))){
            tmp.id=atoi(mysql_row[0]);
            tmp.name=QString(QLatin1String(mysql_row[1]));
            tmp.category=QString(QLatin1String(mysql_row[2]));
            tmp.num=atoi(mysql_row[3]);
            tmp.belong_to=atoi(mysql_row[4]);
            tmp.x=atoi(mysql_row[5]);
            tmp.y=atoi(mysql_row[6]);
            tmp.z=atoi(mysql_row[7]);
            tmp.description=QString(QLatin1String(mysql_row[8]));
            view[tmp.id]=tmp;
        }
    }
}
//删除指定货物id在view中的储存以及在数据库中的存储。
void conitem::delete_item(int ID){
    char cmd[400];
    sprintf(cmd,"delete from item where item.id=%d",ID);
    view.erase(view.find(ID));
    query(cmd);
    return ;
}
//从输入获得货物信息并将其输入数据库中，然后在view中存储该货物的信息，即在数据库与conitem中都添加了输入信息的货物。
void conitem::insert_item(storeitem &u){
    char cmd[400];
    sprintf(cmd,"insert into item(name,category,num,belong_to,x,y,z,description)values(\'%s\',\'%s\',%d,%d,%d,%d,%d,\'%s\')",
            u.name.toLatin1().data(),u.category.toLatin1().data(),u.num,u.belong_to,u.x,u.y,u.z,u.description.toLatin1().data()
            );
    query(cmd);
    sprintf(cmd,"select LAST_INSERT_ID()");
    query(cmd);
    mysql_result=mysql_store_result(&mysql_conn);
    mysql_row=mysql_fetch_row(mysql_result);
    u.id=QString(QLatin1String(mysql_row[0])).toInt();
    view[u.id]=u;
}
//将view和数据库中指定id的货物的数量更新为输入参数。
void conitem::change_num(int ID, int amount)
{
    char cmd[400];
    sprintf(cmd,"update item set num=num+%d where id=%d ",-amount,ID);
    view[ID].num-=amount;
    query(cmd);
    return ;
}

//按条件查询货物并把查找出的货物信息存放在conitem中的view中和ret中，然后把这个ret返回。
//查询条件具体为哪几项由flag值决定。
QString domin[3]={"item.name regexp ","item.category regexp ","item.description regexp "};
QVector<storeitem> conitem::get_item_of_description(int flag,QString kw){
    int ok= false;
    QString str;
    for (int i=0;i<3;i++){
        if ((flag>>i)&1){
            if (ok)str+=" or ";
            ok=true;
            str+=domin[i]+"\'"+kw+"\'";
        }
    }
    //上段代码最终形成结果为str=(domin[0]+'kw')+"or"+(domin[1]+'kw')+"or"+(domin[2]+'kw')
	//具体是什么看flag的二进制值
    //qDebug()<<str;

    char cmd[600];
    sprintf(cmd,"select * from item where %s",str.toStdString().c_str());
    QVector<storeitem> ret;
    if (query(cmd)==0){
        storeitem tmp;
        mysql_result=mysql_store_result(&mysql_conn);
        while ((mysql_row=mysql_fetch_row(mysql_result))){
            tmp.id=atoi(mysql_row[0]);
            tmp.name=QString(QLatin1String(mysql_row[1]));
            tmp.category=QString(QLatin1String(mysql_row[2]));
            tmp.num=atoi(mysql_row[3]);
            tmp.belong_to=atoi(mysql_row[4]);
            tmp.x=atoi(mysql_row[5]);
            tmp.y=atoi(mysql_row[6]);
            tmp.z=atoi(mysql_row[7]);
            tmp.description=QString(QLatin1String(mysql_row[8]));
            view[tmp.id]=tmp;
            ret.push_back(tmp);
        }
    }
    return ret;
}
//按货架id查询货物并把该货架中所有的货物信息存放在conitem中的view中和ret中，然后把这个ret返回,函数输入是货架id。
QVector<storeitem> conitem::get_item_of_shelf(int ID){
    char cmd[600];
    sprintf(cmd,"select * from item where belong_to=%d",ID);
    QVector<storeitem> ret;
    if (query(cmd)==0){
        storeitem tmp;
        mysql_result=mysql_store_result(&mysql_conn);
        while ((mysql_row=mysql_fetch_row(mysql_result))){
            tmp.id=atoi(mysql_row[0]);
            tmp.name=QString(QLatin1String(mysql_row[1]));
            tmp.category=QString(QLatin1String(mysql_row[2]));
            tmp.num=atoi(mysql_row[3]);
            tmp.belong_to=atoi(mysql_row[4]);
            tmp.x=atoi(mysql_row[5]);
            tmp.y=atoi(mysql_row[6]);
            tmp.z=atoi(mysql_row[7]);
            tmp.description=QString(QLatin1String(mysql_row[8]));
            view[tmp.id]=tmp;
            ret.push_back(tmp);
        }
    }
    return ret;
}
