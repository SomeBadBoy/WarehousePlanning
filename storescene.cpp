#include "storescene.h"
#include "shelfdialog.h"
#include "housedialog.h"
//#include <QDebug>
#include <QMessageBox>
//构造函数，需要传入一个QT的窗口基类指针，三个QT的单选按键类指针，conhouse,conshelf,conitem类的指针各一个，
//结果是构造了一个保护数据与传入参数相关联（赋值操作），新建了画图区域和颜色。
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
//鼠标单击事件的各种处理
void storescene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{//鼠标左键按下
    if (this->houseButton->isChecked()){
        curItem=new QGraphicsRectItem;
        addItem(curItem);
        curItem->setRect(QRect(event->scenePos().toPoint(),QSize(0,0)));
        QGraphicsScene::mousePressEvent(event);
        pressed=true;

    }
   //货架修改模式
	else if (this->shelfButton->isChecked())
	{//右键取消已建立的货架
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
			//左键建立货架
        }else {
            curItem=new QGraphicsRectItem;
            addItem(curItem);
            curItem->setRect(QRect(event->scenePos().toPoint(),QSize(0,0)));
            QGraphicsScene::mousePressEvent(event);
            pressed=true;
        }
		//查询单选键选择时，查询每个货架是否包含鼠标点击的点，如果包含则显示该货架信息。
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
//鼠标拖动事件
void storescene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){//鼠标移动事件
    if (!pressed||(!this->houseButton->isChecked() && !this->shelfButton->isChecked())){
        event->ignore();
    }else {
        QRect tmp(curItem->rect().topLeft().toPoint(),event->scenePos().toPoint());
        curItem->setRect(tmp);
        QGraphicsScene::mouseMoveEvent(event);
    }
}
//鼠标释放事件
void storescene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
     if (!pressed||(!this->houseButton && !this->shelfButton)){
         event->ignore();
     }else if (this->shelfButton->isChecked() ){
         pressed=false;
         //storeshelf u;
         //qDebug()<<"go,";
		 //对于每一个货架和新建货架进行碰撞检测，碰撞则删除新建货架
         foreach (const storeshelf &u, shelf->view.values()){
             if (curItem->collidesWithItem(u.figure)){//碰撞检测
                 delete curItem;
                 event->ignore();
                 return ;
             }
         }
//		 storehouse & kk=this->house->house;//增添了对house的碰撞检测
//		 if (curItem->collidesWithItem(kk.figure)){
//                 delete curItem;
//                 event->ignore();
//                 return ;
//             }

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
//		 storehouse & kk = this->house->house;//增添了对house的碰撞检测
//			if (curItem->collidesWithItem(kk.figure)){
//				delete curItem;
//				event->ignore();
//				return ;
//			}
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
