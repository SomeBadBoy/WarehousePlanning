#ifndef CONHOUSE_H
#define CONHOUSE_H
#include <dbms.h>
#include <storehouse.h>
#include <storeshelf.h>
#include <QVector>
class conhouse:public DBMS
{
private:
    storehouse get_house_now();
public:
    conhouse();

    storehouse house;

    //QVector<storeshelf>;
    void insert_house(storehouse&);
    void delete_house();
};

#endif // CONHOUSE_H
