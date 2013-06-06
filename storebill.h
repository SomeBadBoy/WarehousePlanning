#ifndef STOREBILL_H
#define STOREBILL_H

#include <QString>
#include <QVector>
class storebill{
public:
    int id,belong_to;
    bool done;
    QVector<int> node;

    bool operator <(storebill & elem){
        return this->id<elem.id;
    }
};



#endif // STOREBILL_H
