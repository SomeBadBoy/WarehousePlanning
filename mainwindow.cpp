#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <fstream>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QMessageBox>
#include "connectdb.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	connectdb condialog;//获取数据库登陆信息
	condialog.exec();
    house=new conhouse;
    shelf=new conshelf;
    item=new conitem;
    bill=new conbill;
    scene=new storescene(this,ui->houseButton,ui->shelfButton,ui->queryButton,house,shelf,item);
    ui->houseView->setScene(scene);
    ui->houseView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->scene->addItem(bill->path);
    if (house->house.id>0)
        this->scene->addItem(house->house.figure);
    foreach(const storeshelf & u,shelf->view){
        this->scene->addItem(u.figure);
    }
    QObject::connect(this->scene, SIGNAL(display(int)), this, SLOT(get_items_of_shelf(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

#if 0
void MainWindow::on_massOutputButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    QFileInfo info(filename);
    if (info.exists() && info.isFile()) {

        house_rect=new QGraphicsRectItem;
        house_rect->setRect(QRect(QPoint(1,1),QPoint(399,399)));
        this->scene->addItem(house_rect);

        int m;
        fstream fin(filename.toStdString().c_str());
        fin>>n>>m;
        for (int i=0;i<b.size();i++){
            delete b[i];
        }
        a.clear();
        b.clear();
        for (int i=0;i<n;i++){
            int x,y;
            fin>>x>>y;
            //qDebug()<<"{"<<x<<","<<y<<"}";
            a.push_back(Node(x,y,i));
        }
        for (int i=0;i<m;i++){
            int x[2],y[2];
            fin>>x[0]>>y[0]>>x[1]>>y[1];
            b.push_back(new QGraphicsRectItem);
            b[i]->setRect(QRect(QPoint(x[0],y[0]),QPoint(x[1],y[1])));
            this->scene->addItem(b[i]);
            a.push_back(Node(x[0]-2,y[0]-2));
            a.push_back(Node(x[1]+2,y[0]-2));
            a.push_back(Node(x[0]-2,y[1]+2));
            a.push_back(Node(x[1]+2,y[1]+2));
        }
    }
}
void MainWindow::on_pathButton_clicked()
{
    if (a.size()==0||n>15||a.size()>50)return ;

    for (int i=0;i<a.size();i++){
        //qDebug()<<"-"<<a[i].x<<","<<a[i].y;
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
    int state=(1<<n)-1,i=0,j,next;
    for (j=0;j<n;j++)
        if (f[state][j]>f[state][i])
            i=j;
   // qDebug()<<state<<"<"<<i<<"<"<<f[state][i];

    if (f[state][i]<1e200){
        QPolygon ploygon;
        while (state!=0||i!=0){
            //qDebug()<<state<<"<"<<i<<"<"<<a[i].x<<","<<a[i].y;
            ploygon.append(QPoint(a[i].x,a[i].y));
            next=g[state][i].first;
            j=g[state][i].second;
            state=next,i=j;
        }
        path->setPolygon(ploygon);
    }
    pathcolor->setColor(QColor(0,0,192));
    path->setVisible(true);
#endif
    a.clear();
}
#endif


void MainWindow::on_initHouseButton_clicked()//初始化仓库
{


    QVector<int > killer;
    foreach (const storeitem u,item->view)killer.push_back(u.id);//删除所有货物信息
    for (int i=0;i<killer.size();i++)item->delete_item(killer[i]);
    killer.clear();

    foreach (const storeshelf u,shelf->view)killer.push_back(u.id);//删除所有货架信息
    for (int i=0;i<killer.size();i++)shelf->delete_shelf(killer[i]);
    house->delete_house();
}

void MainWindow::on_initInputButton_clicked()//入库初始化表项
{
    ui->inputTable->setColumnCount(0);
    ui->inputTable->setRowCount(0);

    ui->inputTable->setColumnCount(8);//设置列数
    ui->inputTable->setRowCount(18);//设置行数
    QStringList headers;
    headers<<"Name"<<"Category"<<"Amount"<<"Shelf ID"<<"Direction"<<"Colum"<<"Layer"<<"Description";
    ui->inputTable->setHorizontalHeaderLabels(headers);
    for (int i=0;i<18;i++){
        for (int j=0;j<8;j++)
            ui->inputTable->setItem(i,j,new QTableWidgetItem(QString()));//对表项数据进行输入
    }
}

void MainWindow::on_finInputButton_clicked()//表项货物入库
{

    for (int i=0;i<ui->inputTable->rowCount();i++)
        if (ui->inputTable->item(i,0)->text().size()>0){//判断表项是否不为空
            storeitem tmp;
            tmp.name=ui->inputTable->item(i,0)->text();
            tmp.category=ui->inputTable->item(i,1)->text();
            tmp.num=ui->inputTable->item(i,2)->text().toInt();
            tmp.belong_to=ui->inputTable->item(i,3)->text().toInt();
            tmp.x=ui->inputTable->item(i,4)->text().toInt();
            tmp.y=ui->inputTable->item(i,5)->text().toInt();
            tmp.z=ui->inputTable->item(i,6)->text().toInt();
            tmp.description=ui->inputTable->item(i,7)->text();
            item->insert_item(tmp);
            //shelf->view[tmp.belong_to].node.push_back(tmp.id);
        }
    ui->inputTable->setColumnCount(0);//重设表项
    ui->inputTable->setRowCount(0);
}
#include <QDebug>
void MainWindow::on_massInputButton_clicked()//批量入库
{
    QString filename = QFileDialog::getOpenFileName();//选择批量输入文件
    QFileInfo info(filename);
    if (info.exists() && info.isFile()) {
        int m;
        FILE *fp=fopen(filename.toStdString().c_str(),"r");
        //ifstream fin(filename.toStdString().c_str());
        fscanf(fp,"%d\n",&m);//从fp中读入整数，存入m中
        //qDebug()<<"m="<<m;
        storeitem tmp;
        char name[200],category[200],description[200];
        int num,belong_to,x,y,z;
        for (int i=0;i<m;i++){
            fscanf(fp,"%[^\t]\t%[^\t]\t%d%d%d%d%d\t%[^\n]\n",name,category,&num,&belong_to,&x,&y,&z,description);
            tmp.name=QString(name);
            tmp.category=QString(category);
            tmp.num=num;
            tmp.belong_to=belong_to;
            tmp.x=x;
            tmp.y=y;
            tmp.z=z;
            tmp.description=QString(description);
            item->insert_item(tmp);
        }
        fclose(fp);
    }
}

void MainWindow::on_initOutputButton_clicked()//出库初始化表项
{
    ui->outputTable->setColumnCount(0);
    ui->outputTable->setRowCount(0);

    ui->outputTable->setColumnCount(3);//设列数
    ui->outputTable->setRowCount(14);//设行数
    QStringList headers;
    headers<<"Name"<<"Category"<<"Amount";
    ui->outputTable->setHorizontalHeaderLabels(headers);
    for (int i=0;i<14;i++){
        for (int j=0;j<8;j++)
            ui->outputTable->setItem(i,j,new QTableWidgetItem(QString()));
    }
}

void MainWindow::on_pathButton_clicked()//显示路径
{
    QVector<QPair<QPair<QString,QString>,int> > keyword;
    ///qDebug()<<ui->outputTable->rowCount();
    for (int i=0;i<(int)ui->outputTable->rowCount();i++){
        QString name    =ui->outputTable->item(i,0)->text();
        QString category=ui->outputTable->item(i,1)->text();
        QString num     =ui->outputTable->item(i,2)->text();
        if (name.size()==0||category.size()==0||num.size()==0){
            continue;
        }
        QPair<QPair<QString,QString>,int> tmp=qMakePair(qMakePair(name,category),num.toInt());
        //qDebug()<<i<<","<<name<<","<<category<<num;
        keyword.push_back(tmp);
    }
    //qDebug()<<scene->beg->pos().x()<<scene->beg->pos().y();
    bill->find_path(shelf,item,keyword,scene->beg->x(),scene->beg->y());
    bill->path->setVisible(true);
    for (int i=0;i<bill->point.size();i++){
        this->scene->addItem(bill->point[i]);
    }
}

void MainWindow::on_finOutputButton_clicked()//表项货物出库
{
    ui->outputTable->setColumnCount(0);
    ui->outputTable->setRowCount(0);
    bill->make_deal(shelf,item);
    return ;
}

void MainWindow::on_massOutputButton_clicked()//批量出库
{

    QVector<QPair<QPair<QString,QString>,int> > keyword;
    QString filename = QFileDialog::getOpenFileName();
    QFileInfo info(filename);
    if (info.exists() && info.isFile()) {
        qDebug()<<"-1";
        FILE *fp=fopen(filename.toStdString().c_str(),"r");
        int m;
        fscanf(fp,"%d\n",&m);
        char name [200],category[200];
        int num;
        for(int i=0;i<m;i++){
            fscanf(fp,"%[^\t]\t%[^\t]%d\n",name,category,&num);
            QPair<QPair<QString,QString>,int> tmp=qMakePair(qMakePair(QString(name),QString(category)),num);
            keyword.push_back(tmp);
            qDebug()<<"i="<<i;
        }
        fclose(fp);
    }
    qDebug()<<"0";
    bill->find_path(shelf,item,keyword,scene->beg->x(),scene->beg->y());
    bill->path->setVisible(true);
    for (int i=0;i<bill->point.size();i++){
        this->scene->addItem(bill->point[i]);
    }
    //bill->massOUT(shelf,item,keyword);
}

QString direct[4]={"North","South","East","West"};

void MainWindow::on_searchButton_clicked()//检索货物
{
    ui->searchTable->setColumnCount(0);
    ui->searchTable->setRowCount(0);
    QString keyword=ui->keywordEdit->text();
    int flag=0;
    if (ui->nameBox->isChecked())flag|=1;
    if (ui->categoryBox->isChecked())flag|=2;
    if (ui->desBox->isChecked())flag|=4;
    if (flag==0)return ;
    QVector<storeitem> result=item->get_item_of_description(flag,keyword);
    ui->searchTable->setColumnCount(8);
    ui->searchTable->setRowCount(result.size());
    QStringList headers;
    headers<<"Name"<<"Category"<<"Amount"<<"Shlef"<<"Direction"<<"Column"<<"Layer"<<"Description";
    ui->searchTable->setHorizontalHeaderLabels(headers);
    for (int i=0;i<(int)result.size();i++){
        ui->searchTable->setItem(i,0,new QTableWidgetItem(result[i].name));
        ui->searchTable->setItem(i,1,new QTableWidgetItem(result[i].category));
        ui->searchTable->setItem(i,2,new QTableWidgetItem(QString::number(result[i].num)));
        ui->searchTable->setItem(i,3,new QTableWidgetItem(shelf->view[result[i].belong_to].name));
        ui->searchTable->setItem(i,4,new QTableWidgetItem(direct[result[i].x]));
        ui->searchTable->setItem(i,5,new QTableWidgetItem(QString::number(result[i].y)));
        ui->searchTable->setItem(i,6,new QTableWidgetItem(QString::number(result[i].z)));
        ui->searchTable->setItem(i,7,new QTableWidgetItem(result[i].description));
    }
}

void MainWindow::get_items_of_shelf(int id){
    ui->searchTable->setColumnCount(0);
    ui->searchTable->setRowCount(0);
    QVector<storeitem> result=item->get_item_of_shelf(id);
    ui->searchTable->setColumnCount(8);
    ui->searchTable->setRowCount(result.size());
    QStringList headers;
    headers<<"Name"<<"Category"<<"Amount"<<"Shlef"<<"Direction"<<"Column"<<"Layer"<<"Description";
    ui->searchTable->setHorizontalHeaderLabels(headers);
    for (int i=0;i<(int)result.size();i++){
        ui->searchTable->setItem(i,0,new QTableWidgetItem(result[i].name));
        ui->searchTable->setItem(i,1,new QTableWidgetItem(result[i].category));
        ui->searchTable->setItem(i,2,new QTableWidgetItem(QString::number(result[i].num)));
        ui->searchTable->setItem(i,3,new QTableWidgetItem(shelf->view[result[i].belong_to].name));
        ui->searchTable->setItem(i,4,new QTableWidgetItem(direct[result[i].x]));
        ui->searchTable->setItem(i,5,new QTableWidgetItem(QString::number(result[i].y)));
        ui->searchTable->setItem(i,6,new QTableWidgetItem(QString::number(result[i].z)));
        ui->searchTable->setItem(i,7,new QTableWidgetItem(result[i].description));
    }
}
