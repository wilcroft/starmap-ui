#include "starmapui.h"
#include "ui_starmapui.h"

StarMapUI::StarMapUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StarMapUI)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);

    connect (ui->actionOpen, SIGNAL(triggered()),
             this, SLOT(openMap()));
    connect (ui->actionNew, SIGNAL(triggered()),
             this, SLOT(newMap()));
    connect (ui->actionExit, SIGNAL(triggered()),
             this, SLOT(exitApp()));
    mapExists = false;

    mapScene = new QGraphicsScene;
   // mapItem = new QGraphicsPixmapItem(QPixmap("output.png"));

 //   mapScene->addItem(mapItem);

 //   ui->mapDisplay->setScene(mapScene);
    ui->mapDisplay->setMouseTracking(true);
    ui->starTypeLabel->setText("");
    ui->starSizeLabel->setText("");
    setMouseTracking(true);

    count = 0;

}

StarMapUI::~StarMapUI()
{
    if (mapExists){
        delete starMap;
        delete mapItem;
    }
    delete mapScene;
    delete ui;
}

void StarMapUI::newMap()
{
    qDebug() << "New!";

    if (mapExists){
        delete starMap;
        delete mapItem;
    }

    starMap = new Map(200,200);
    mapItem = new QGraphicsPixmapItem(QPixmap("output.png"));
    mapScene->addItem(mapItem);

    ui->mapDisplay->setScene(mapScene);

    mapExists = true;
}

void StarMapUI::openMap()
{
    bool ok;
    int seed = QInputDialog::getInt(this, tr("Open Seed..."),tr("Seed:"), 0,
                                   -2147483647,2147483647,1,&ok);
    qDebug() << "Open!" << seed;
    if (ok){
        if (mapExists){
            delete starMap;
            delete mapItem;
        }
        starMap = new Map(200,200, seed);
        mapItem = new QGraphicsPixmapItem(QPixmap("output.png"));
        mapScene->addItem(mapItem);

        ui->mapDisplay->setScene(mapScene);

        mapExists = true;


    }
}

void StarMapUI::exitApp()
{
    qDebug() << "Exit!";
    close();
}
/*
void StarMapUI::mouseMoveEvent(QMouseEvent* event){
    int x = event->pos().x();
    int y = event->pos().y();

    QString labelString=QString("(%1,%2)").arg(x,y);

    ui->starLabel->setText(labelString);
}*/

bool StarMapUI::eventFilter(QObject *obj, QEvent *event){
//    if (event->type() == QEvent::MouseMove){
//        qDebug() << obj->objectName();
//        qDebug() << "~~~~~ " << count;
//        count++;
//    }
//    if (mapExists && event->type() == QEvent::MouseButtonPress){
//        qDebug() << obj->objectName();
//        qDebug() << "~~~~~ " << count;
//        count++;
//    }
    if (mapExists && event->type() == QEvent::MouseButtonPress && obj==ui->mapDisplay){
//        qDebug() << obj->objectName();
//        if (obj->objectName()==ui->mapDisplay->objectName())
//            qDebug() << "MATCH";
//        else
//            qDebug() << "NOPE";
//        if (obj==ui->mapDisplay)
//            qDebug() << "SAME";
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        //QString labelString=QString("(%1,%2)").arg(QString::number(mouseEvent->x()),
        //                                           QString::number(mouseEvent->y()));
        Star* star = starMap->getStar(mouseEvent->x()/4,mouseEvent->y()/4);
        qDebug() << "(" << mouseEvent->x() << "," << mouseEvent->y() << ")";

        qDebug() << " => (" << mouseEvent->x()/4 << "," << mouseEvent->y()/4 << ")";
        QString sizeString, typeString;
        if (star==nullptr){
            sizeString="";
            typeString="";
        }
        else{
            switch (star->getType()){
                case TYPE_RED:
                        typeString = "RED ";
                        break;
                case TYPE_YELLOW:
                        typeString = "YELLOW ";
                        break;
                case TYPE_ORANGE:
                        typeString = "ORANGE ";
                        break;
                case TYPE_WHITE:
                        typeString = "WHITE ";
                        break;
                case TYPE_BLUE:
                        typeString = "BLUE ";
                        break;
                case TYPE_BLUEWHITE:
                        typeString = "BLUE-WHITE ";
                        break;
                case TYPE_BLUEVIOLET:
                        typeString = "BLUE-VIOLET ";
            }
            switch (star->getSize()){
                case DWARF:
                    sizeString += "DWARF";
                    break;
                case GIANT:
                    sizeString += "GIANT";
                    break;
                case SUPERGIANT:
                    sizeString += "SUPERGIANT";
                    break;
            }
        }
        ui->starTypeLabel->setText(typeString);
        ui->starSizeLabel->setText(sizeString);
    }
    return false;
}
