#ifndef STORESHELF_H
#define STORESHELF_H

#include <QString>
#include <QGraphicsRectItem>
#include <QVector>
class storeshelf{
public:

#if 1
    storeshelf(){
        figure=NULL;
    }
    ~storeshelf(){
        //delete figure;
    }

    QGraphicsRectItem *figure;
    int x,y,z;
    int id,belong_to,thin;
    QString name,description;
    //QVector<int> node;

    bool operator <(storeshelf & elem){
        return this->id<elem.id;
    }
#endif
};
#endif // STORESHELF_H
