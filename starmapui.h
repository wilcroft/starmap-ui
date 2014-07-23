#ifndef STARMAPUI_H
#define STARMAPUI_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <QInputDialog>
#include <QMouseEvent>
#include <QString>

#include "cli_tools/map.h"
#include "cli_tools/star.h"
#include "cli_tools/util.h"

namespace Ui {
class StarMapUI;
}

/*
class MyGraphicsView: public QGraphicsView{

public:
    MyView(QGraphicsScene* qscene):QGraphicsView(qscene){
        setMouseTracking(true);
     //   QGraphicsView(qscene);
    }
    ~MyView(){}
    void mousePressEvent(QMouseEvent * event){
        QString string;
        QTextStream out(stdout);
        Star* starptr;
        //char str[50];
        //sprintf(str,"(%d,%d)\n",event->x(), event->y());
       // string = str;
        //this->setWindowTitle(string);
        //out << "(" << event->x() << "," << event->y() << ")" << endl;
        //out << "(" << event->globalX() << "," << event->globalY() << ")" << endl;
        starptr = myMap->getStar(event->x()/4, event->y()/4);
        if (starptr!=nullptr){
            starptr->printStarInfo();
        }
        else{
            out << "No Star at (" << event->x()/4 << "," << event->y()/4 << ")" << endl;
        }
        QString labelString=QString("(%1,%2)").arg(QString::number(event->pos().x()),
                                                   QString::number(event->pos().y()));
        ui->starLabel->setText(labelString);

    }

    void linkUI(Ui::StarMapUI* src){ui=src;}

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::StarMapUI* ui;

};*/

class StarMapUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit StarMapUI(QWidget *parent = 0);
    ~StarMapUI();

protected:
//    void mouseMoveEvent(QMouseEvent* event);
    bool eventFilter(QObject *, QEvent *);

private slots:
    void newMap();

    void openMap();

    void exitApp();

private:
    Ui::StarMapUI *ui;
    QGraphicsScene* mapScene;
    QGraphicsPixmapItem* mapItem;
    QGraphicsView* mapView;

    Map* starMap;
    bool mapExists;
    int count;

};

#endif // STARMAPUI_H
