#ifndef STORESCENE_H
#define STORESCENE_H

#include <QGraphicsScene>
#include <QRadioButton>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <conhouse.h>
#include <conshelf.h>
#include <conitem.h>
#include <QGraphicsEllipseItem>
class storescene : public QGraphicsScene
{
    Q_OBJECT
public:
    QGraphicsEllipseItem * beg;
    storescene(QWidget *parent,QRadioButton* button1,QRadioButton*button2,QRadioButton *button3,conhouse * hou,conshelf *she,conitem * it);
signals:
    void display(int id);
public slots:
protected:
    bool pressed;
    QRadioButton* houseButton,*shelfButton,*queryButton;
    conhouse * house;
    conshelf * shelf;
    conitem * item;
    QGraphicsRectItem *curItem;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // STORESCENE_H
