#ifndef STOREHOUSE_H
#define STOREHOUSE_H

#include <QString>
#include <QGraphicsRectItem>
#include <QVector>
class storehouse{
public:
    storehouse(){
        figure=NULL;
    }
    ~storehouse(){
        //delete figure;
    }

    QGraphicsRectItem * figure;
    QString name,description;
    int id;
    int x,y;
    //QVector<int> node;

    bool operator <(storehouse & elem){
        return this->id<elem.id;
    }
};

#endif // STOREHOUSE_H
