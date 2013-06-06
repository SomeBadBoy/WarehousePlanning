#include "conbill.h"
#include <iostream>
#include <QMessageBox>
#include <cmath>
#include <QQueue>
//#include <QDebug>
using namespace std;
conbill::conbill()
{
    path=new QGraphicsPolygonItem;
    pathcolor=new QGraphicsColorizeEffect;
    path->setGraphicsEffect(pathcolor);
}

void conbill::find_path(conshelf *shelf,conitem *item,QVector<QPair<QPair<QString,QString>,int> > &keyword ,int x,int y){
    decs=QVector<int>(item->view.size(),0);
   // for (int i=0;i<keyword.size();i++)
        //qDebug()<<"@"<<keyword[i].first.first<<keyword[i].first.second<<keyword[i].second;

    //qDebug()<<"x="<<x<<",y="<<y;
    int j=0;
    n=0;
    a.clear();
    b.clear();
    to_do.clear();
    a.push_back(Node(x,y,n));
    n++;
    //qDebug()<<"1";
    foreach(const storeitem & u,item->view){
        for (int i=0;i<keyword.size();i++)
            if (qMakePair(u.name,u.category)==keyword[i].first){
                int tmp=min(u.num-decs[j],keyword[i].second);
                decs[j]+=tmp;
                keyword[i].second-=tmp;
            }
        if (decs[j]>0){
            a.push_back(shelf->toNode(u,n));
            n++;
            to_do.push_back(qMakePair(u.id,decs[j]));
        }
        //qDebug()<<"!!"<<j<<u.name<<u.category<<u.num<<decs[j];
        j++;
    }

    //qDebug()<<"2";
    for (int i=0;i<keyword.size();i++)
        if (keyword[i].second>0){
            //qDebug()<<keyword[i].first.first<<keyword[i].first.second<<keyword[i].second;
            QMessageBox::information(NULL, "Warning", "Not enough books.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return ;
        }

    //qDebug()<<"3";
    foreach(const storeshelf &u,shelf->view){
        b.push_back(u.figure);
        QRect tmp=u.figure->rect().toRect();
        //qDebug()<<tmp.top()<<tmp.left;
        a.push_back(Node(tmp.left()-3,tmp.top()-3));
        a.push_back(Node(tmp.left()-3,tmp.bottom()+3));
        a.push_back(Node(tmp.right()+3,tmp.top()-3));
        a.push_back(Node(tmp.right()+3,tmp.bottom()+3));
    }

    if (a.size()==0||n>15||a.size()>50){
        QMessageBox::information(NULL, "Warning", "Too many books to find a suitable path.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    //qDebug()<<n<<a.size();
    for (int i=0;i<point.size();i++)
        delete point[i];
    point.clear();
    for (int i=0;i<a.size();i++){
        //qDebug()<<"-"<<a[i].x<<","<<a[i].y<<","<<a[i].id;

        for (int j=i+1;j<a.size();j++){
            int ok=0;
            QLine Line(QPoint(a[i].x,a[i].y),QPoint(a[j].x,a[j].y));
            QGraphicsLineItem line(Line);
            for (int k=0;k<b.size();k++)
                if (b[k]->collidesWithItem(&line)){
                    ok=k+1;
                    break;
                }
            if (ok==0){
                double length=sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
                a[i].e.push_back(QPair<int,double>(j,length));
                a[j].e.push_back(QPair<int,double>(i,length));
            }
           // if (i<n)qDebug()<<i<<"-"<<j<<"-"<<ok;
            //if (i<n)qDebug()<<"i="<<i<<",j="<<j<<","<<a[i].x<<","<<a[i].y<<"<->"<<a[j].x<<","<<a[j].y;
        }
    }
    //qDebug()<<a.size();
#if 1
    f=QVector<QVector<double> >(1<<n,QVector<double>(a.size(),1e200));
    g=QVector<QVector<QPair<int,int> > >(1<<n,QVector<QPair<int,int> >   (a.size()));
    f[1][0]=0;
    QQueue<QPair<int,int> > que;
    que.push_back(QPair<int,int>(1,0));

    while (!que.empty()){
        int i=que.front().second,state=que.front().first;
        que.pop_front();
            for (int cur=0;cur<a[i].e.size();cur++){
                int j=a[i].e[cur].first;
                int next=state;
                if (j<n)next|=1<<j;
                if (f[state][i]+a[i].e[cur].second<f[next][j]){
                    f[next][j]=f[state][i]+a[i].e[cur].second;
                    g[next][j]=QPair<int,int>(state,i);
                    que.push_back(QPair<int,int>(next,j));

                       //qDebug()<<"next="<<next<<"!!"<<j<<",i="<<i<<",",f[next][j];

                }
            }

    }
    int state=(1<<n)-1,i=0,next;
    for (j=0;j<n;j++)
        if (f[state][j]>f[state][i])
            i=j;
   // qDebug()<<state<<"<"<<i<<"<"<<f[state][i];

    if (f[state][i]<1e200){
        QPolygon ploygon;
        while (state!=0||i!=0){
            if (i<n){
                QGraphicsEllipseItem * p= new QGraphicsEllipseItem(-2,-2,2,2);
                p->setPos(a[i].x,a[i].y);
                point.push_back(p);
            }
            //qDebug()<<state<<"<"<<i<<"<"<<a[i].x<<","<<a[i].y<<","<<a[i].id;
            ploygon.append(QPoint(a[i].x,a[i].y));
            next=g[state][i].first;
            j=g[state][i].second;
            state=next,i=j;
        }
        path->setPolygon(ploygon);
    }
    pathcolor->setColor(QColor(255,0,0));
    path->setVisible(true);
#endif
    a.clear();
}
void conbill::make_deal(conshelf *shelf,conitem *item){
    path->setVisible(false);
    foreach(const QGraphicsEllipseItem * p,point){
        delete p;
    }
    point.clear();

    for (int i=0;i<(int)to_do.size();i++){
        if (item->view[to_do[i].first].num==to_do[i].second){
            item->delete_item(to_do[i].first);
        }else {
            item->change_num(to_do[i].first,to_do[i].second);
        }
    }
    to_do.clear();
}

void conbill::massOUT(conshelf *shelf,conitem *item,QVector<QPair<QPair<QString,QString>,int> > &keyword )
{

    decs=QVector<int>(item->view.size(),0);
    int j=0;
    n=0;
    a.clear();
    b.clear();
    to_do.clear();
    foreach(const storeitem & u,item->view){
        for (int i=0;i<keyword.size();i++)
            if (qMakePair(u.name,u.category)==keyword[i].first){
                int tmp=min(u.num-decs[j],keyword[i].second);
                decs[j]+=tmp;
                keyword[i].second-=tmp;
            }
        if (decs[j]>0){
            a.push_back(shelf->toNode(u,n));
            n++;
            to_do.push_back(qMakePair(u.id,decs[j]));
        }
        j++;
    }

    for (int i=0;i<keyword.size();i++)
        if (keyword[i].second>0){
            QMessageBox::information(NULL, "Warning", "Not enough books.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return ;
        }
    make_deal(shelf,item);
}
