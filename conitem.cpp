#include "conitem.h"

//���캯���������ݿ��л����������Ϣȫ��ȡ����������conitem���QMap������view�У�
//����view�ǻ���id��storeitem���Ӧ��
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
//ɾ��ָ������id��view�еĴ����Լ������ݿ��еĴ洢��
void conitem::delete_item(int ID){
    char cmd[400];
    sprintf(cmd,"delete from item where item.id=%d",ID);
    view.erase(view.find(ID));
    query(cmd);
    return ;
}
//�������û�����Ϣ�������������ݿ��У�Ȼ����view�д洢�û������Ϣ���������ݿ���conitem�ж������������Ϣ�Ļ��
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
//��view�����ݿ���ָ��id�Ļ������������Ϊ���������
void conitem::change_num(int ID, int amount)
{
    char cmd[400];
    sprintf(cmd,"update item set num=num+%d where id=%d ",-amount,ID);
    view[ID].num-=amount;
    query(cmd);
    return ;
}

//��������ѯ���ﲢ�Ѳ��ҳ��Ļ�����Ϣ�����conitem�е�view�к�ret�У�Ȼ������ret���ء�
//��ѯ��������Ϊ�ļ�����flagֵ������
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
    //�϶δ��������γɽ��Ϊstr=(domin[0]+'kw')+"or"+(domin[1]+'kw')+"or"+(domin[2]+'kw')
	//������ʲô��flag�Ķ�����ֵ
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
//������id��ѯ���ﲢ�Ѹû��������еĻ�����Ϣ�����conitem�е�view�к�ret�У�Ȼ������ret����,���������ǻ���id��
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
