#ifndef CONSHELF_H
#define CONSHELF_H

#include <storeshelf.h>
#include <QMap>
#include <storeitem.h>
#include <dbms.h>
#include <QVector>

struct Node{
    int x,y;
    int id;
    QVector<QPair<int,double> > e;
    Node(){
        id=-1;
        e.clear();
    }
    Node (int a,int b){
        id=-1;
        e.clear();
        x=a;
        y=b;
    }
    Node(int a,int b,int c){
        id=-1;
        e.clear();
        x=a;
        y=b;
        id=c;
    }
};

class conshelf : public DBMS
{
public:
    conshelf();

    QMap<int,storeshelf> view;

    void insert_shelf(storeshelf&);
    void delete_shelf(int);
    Node toNode(const storeitem & u,int id);
    //QVector<storeitem> get_item_of_shelf(int);
};

#endif // CONSHELF_H
