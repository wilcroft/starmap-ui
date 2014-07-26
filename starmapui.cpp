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

//Assign planet labels and views to an array for easy access!
    planetLabelPtr[0]=ui->planetOneLabel;
    planetLabelPtr[1]=ui->planetTwoLabel;
    planetLabelPtr[2]=ui->planetThreeLabel;
    planetLabelPtr[3]=ui->planetFourLabel;
    planetLabelPtr[4]=ui->planetFiveLabel;

    planetViewPtr[0]=ui->planetOneView;
    planetViewPtr[1]=ui->planetTwoView;
    planetViewPtr[2]=ui->planetThreeView;
    planetViewPtr[3]=ui->planetFourView;
    planetViewPtr[4]=ui->planetFiveView;

    setMouseTracking(true);

    starItem = new QGraphicsPixmapItem;
    starScene = new QGraphicsScene;
    starScene->addItem(starItem);

    for (int i=0;i<5;i++){
        planetItem[i]=new QGraphicsPixmapItem;
        planetScene[i]= new QGraphicsScene;
        planetScene[i]->addItem(planetItem[i]);
    }

    count = 0;
    this->clearSidebar();

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
    QString newTitle;

    if (mapExists){
        delete starMap;
        delete mapItem;
    }

    starMap = new Map(200,200);
    mapItem = new QGraphicsPixmapItem(QPixmap("output.png"));
    mapScene->addItem(mapItem);

    ui->mapDisplay->setScene(mapScene);

    mapExists = true;
    newTitle = QString("StarMapUI (%1)").arg(starMap->getMapSeed());
    this->setWindowTitle(newTitle);
    this->clearSidebar();
}

void StarMapUI::openMap()
{
    bool ok;
    QString newTitle;
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
        newTitle = QString("StarMapUI (%1)").arg(seed);
        this->setWindowTitle(newTitle);
        this->clearSidebar();


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
        QString sizeString, typeString,imageString;
        QString planetString[5];
        QString planetImageString[5];
        if (star==nullptr){
            sizeString="";
            typeString="";
            imageString="starpics/nostar.png";
            for (int i=0;i<5;i++){
                planetString[i]="";
                planetImageString[i]="starpics/noplanet.png";
            }
        }
        else{
            sizeString = QString::fromStdString(star->getSizeString());
            typeString = QString::fromStdString(star->getTypeString());
            imageString = "starpics/" + typeString.toLower() + sizeString.toLower() + ".png";
            for (int i=0;i<5;i++){
                planetString[i]=QString::fromStdString(star->getPlanetString(i));
                if (star->getPlanetType(i)==PLANETTYPE_NOPLANET)
                    planetImageString[i]="starpics/noplanet.png";
                else if (star->getPlanetType(i)==PLANETTYPE_GAS)
                    planetImageString[i]="starpics/gasgiant.png";
                else
                    planetImageString[i]="starpics/" + QString::fromStdString(star->getPlanetSizeString(i)).toLower()
                            + QString::fromStdString(star->getPlanetBiomeString(i)).toLower() + ".png";
            }
        /*    switch (star->getType()){
                case TYPE_RED:
                        typeString = "RED";
                        break;
                case TYPE_YELLOW:
                        typeString = "YELLOW";
                        break;
                case TYPE_ORANGE:
                        typeString = "ORANGE";
                        break;
                case TYPE_WHITE:
                        typeString = "WHITE";
                        break;
                case TYPE_BLUE:
                        typeString = "BLUE";
                        break;
                case TYPE_BLUEWHITE:
                        typeString = "BLUE-WHITE";
                        break;
                case TYPE_BLUEVIOLET:
                        typeString = "BLUE-VIOLET";
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
            }*/
        }
        qDebug() << imageString;
        ui->starTypeLabel->setText(typeString);
        ui->starSizeLabel->setText(sizeString);
        starItem->setPixmap(QPixmap(imageString));
        ui->starDisplay->setScene(starScene);

        for (int i=0; i<5;i++){
            //planetLabelPtr[i]->setText(planetString[i]);
            this->setScaledText(planetLabelPtr[i], planetString[i]);
            planetItem[i]->setPixmap(QPixmap(planetImageString[i]));
            planetViewPtr[i]->setScene(planetScene[i]);
        }

    }
    return false;
}

void StarMapUI::setScaledText(QLabel* label, QString text, int maxpt){
    QString fontString;
    
    double length=label->width()+1;
    int pt;
    //int pt=label->font().pointSize()+1;
    if (maxpt==0)
        pt=label->font().pointSize()+1;
    else
        pt=maxpt+1;
    fontString=label->font().family();
    qDebug() << text << ":" << length << " @ " << pt-1;
    while (length>label->width()-5){
        pt--; //start with i=default
        QFont font (fontString, pt);
        QFontMetricsF fm(font);
    //    length = fm.width(text);
        length = fm.maxWidth()*(text.length()+1);
        qDebug() << "\tAt " << pt << " pt, length is " << length << "(" << fm.maxWidth() << "/char)";
        qDebug() << fm.boundingRect(text).width();
    }
    QFont newFont = label->font();
    newFont.setPointSize(pt);
    label->setFont(newFont);
    label->setText(text);
}
void StarMapUI::clearSidebar(){
    ui->starTypeLabel->setText("");
    ui->starSizeLabel->setText("");
    starItem->setPixmap(QPixmap("starpics/nostar.png"));
    ui->starDisplay->setScene(starScene);

    for (int i=0; i<5;i++){
        this->setScaledText(planetLabelPtr[i], "");
        planetItem[i]->setPixmap(QPixmap("starpics/noplanet.png"));
        planetViewPtr[i]->setScene(planetScene[i]);
    }

}
