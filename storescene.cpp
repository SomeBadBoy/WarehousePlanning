#include "storescene.h"
#include "shelfdialog.h"
#include "housedialog.h"
//#include <QDebug>
#include <QMessageBox>
storescene::storescene(QWidget *parent, QRadioButton *button1, QRadioButton *button2,QRadioButton *button3, conhouse *hou, conshelf *she,conitem * it)
    :QGraphicsScene(parent)
{
    houseButton=button1;
    shelfButton=button2;
    queryButton=button3;
    house=hou;
    shelf=she;
    item=it;
    pressed=false;
    beg=new QGraphicsEllipseItem(QRect(-2,-2,2,2));
    beg->setVisible(true);
    QBrush brush(QColor(0,0,255));
    beg->setBrush(brush);
    this->addItem(beg);
    this->setSceneRect(0,0,400,400);
}

void storescene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (this->houseButton->isChecked()){
        curItem=new QGraphicsRectItem;
        addItem(curItem);
        curItem->setRect(QRect(event->scenePos().toPoint(),QSize(0,0)));
        QGraphicsScene::mousePressEvent(event);
        pressed=true;

    }else if (this->shelfButton->isChecked()){
        if (event->button()==Qt::RightButton){
            storeshelf u;
            foreach( u,shelf->view){
                if (u.figure->contains(event->scenePos().toPoint())){
                    QVector<int >killer;
                    foreach(const storeitem & v,item->view)
                        if (v.belong_to==u.id)killer.push_back(v.id);
                    foreach (const int &i, killer)
                        item->delete_item(i);
                    shelf->delete_shelf(u.id);
                    break;
                }
            }
            return ;
        }else {
            curItem=new QGraphicsRectItem;
            addItem(curItem);
            curItem->setRect(QRect(event->scenePos().toPoint(),QSize(0,0)));
            QGraphicsScene::mousePressEvent(event);
            pressed=true;
        }
    }else if (this->queryButton->isChecked()){
        storeshelf u;
        foreach( u,shelf->view){
            if (u.figure->contains(event->scenePos().toPoint()))
            {
                emit display(u.id);
                QString str=QString("The ID of the shelf '<font color='blue'>")+ u.name+QString("</font>' is <font color='red'>")+QString::number(u.id) +QString("</font>.");
                str+=QString("\n The column of the shelf is <font color='red'>")+QString::number(u.y) +"</font>.";
                str+=QString("\n The layer of the shelf is <font color='red'>")+QString::number(u.z) +"</font>.";
                QMessageBox::about(NULL, "Shelf Infomation",str);
                return;
            }
        }
        beg->setPos(event->scenePos());
        //qDebug()<<"$"<<beg->x()<<beg->y();
        return ;
    }else {
        event->ignore();
    }
    return ;
}

void storescene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (!pressed||(!this->houseButton->isChecked() && !this->shelfButton->isChecked())){
        event->ignore();
    }else {
        QRect tmp(curItem->rect().topLeft().toPoint(),event->scenePos().toPoint());
        curItem->setRect(tmp);
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void storescene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
     if (!pressed||(!this->houseButton && !this->shelfButton)){
         event->ignore();
     }else if (this->shelfButton->isChecked() ){
         pressed=false;
         //storeshelf u;
         //qDebug()<<"go,";
         foreach (const storeshelf &u, shelf->view.values()){
             if (curItem->collidesWithItem(u.figure)){
                 delete curItem;
                 event->ignore();
                 return ;
             }
         }
         //qDebug()<<"arrive!";
         shelfdialog dialog(curItem);
         if (dialog.exec()){
             if (house->house.id>=0){
                 dialog.now.belong_to=house->house.id;
                shelf->insert_shelf(dialog.now);
             }else {
                 delete curItem;
             }
         }else {
             delete curItem;
         }
         QGraphicsScene::mouseMoveEvent(event);
     }else if (this->houseButton->isChecked()){
         pressed=false;
         //storeshelf u;
         //qDebug()<<"go!"<<shelf->view.size();
         foreach (const storeshelf &u, shelf->view.values()){
             if (curItem->collidesWithItem(u.figure)){
                 delete curItem;
                 event->ignore();
                 return ;
             }
         }
         housedialog dialog(curItem);
         if (dialog.exec()){
             //qDebug();
             house->insert_house(dialog.now);
         }else {
             delete curItem;
         }
         QGraphicsScene::mouseMoveEvent(event);
     }
}
