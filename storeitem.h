#ifndef STOREITEM_H
#define STOREITEM_H
#include <QString>

class storeitem
{
public:
    storeitem(){
    }

    int x,y,z;
    int id,belong_to;
    int num;
    QString name,category,description;

    bool operator <(storeitem & elem){
        return this->id<elem.id;
    }
};

#endif // STOREITEM_H
