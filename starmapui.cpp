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

    mapFont.setFamily("Courier");

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
    userDim = ui->mapDisplay->width();
    starMap = new Map(150,150);
    mapItem = new QGraphicsPixmapItem(QPixmap("output.png"));
    mapScene->addItem(mapItem);

    ui->mapDisplay->setScene(mapScene);

    mapExists = true;
    newTitle = QString("StarMapUI (%1)").arg(starMap->getMapSeed());
    this->setWindowTitle(newTitle);
    this->clearSidebar();

    addPlayerMarkers();
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
        userDim = ui->mapDisplay->width();
        starMap = new Map(150,150, seed);
        mapItem = new QGraphicsPixmapItem(QPixmap("output.png"));
        mapScene->addItem(mapItem);

        ui->mapDisplay->setScene(mapScene);

        mapExists = true;
        newTitle = QString("StarMapUI (%1)").arg(seed);
        this->setWindowTitle(newTitle);
        this->clearSidebar();

        addPlayerMarkers();
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
        int mx = mouseEvent->x();
        int my = mouseEvent->y();
        //QString labelString=QString("(%1,%2)").arg(QString::number(mouseEvent->x()),
        //                                           QString::number(mouseEvent->y()));
        Star* star = starMap->getStar(mx/5,my/5);
        qDebug() << "(" << mx << "," << my << ")";

        qDebug() << " => (" << mx/5 << "," << my/5 << ")";
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
        }
        qDebug() << imageString;
        this->setScaledText(ui->starTypeLabel,typeString,30);
        this->setScaledText(ui->starSizeLabel,sizeString,30);
        starItem->setPixmap(QPixmap(imageString));
        ui->starDisplay->setScene(starScene);

        for (int i=0; i<5;i++){
            //planetLabelPtr[i]->setText(planetString[i]);
            this->setScaledText(planetLabelPtr[i], planetString[i]);
            planetItem[i]->setPixmap(QPixmap(planetImageString[i]));
            planetViewPtr[i]->setScene(planetScene[i]);
        }/*
        if (star!=nullptr){
            while (starMap->getStar(mx/5-1,my/5)==star){
                mx-=5;
            }
            while (starMap->getStar(mx/5,my/5-1)==star){
                my-=5;
            }
            star = starMap->getStar(mx/5,my/5);
            star->setOwner(STARMAPPLAYER_ONE);
            rgb_t pcolor = getPlayerColor(star->getOwner());
            QPen pen(QColor::fromRgb(pcolor.r,pcolor.g,pcolor.b));
            pen.setWidth(1);
            int rx,ry,rw,rh;
            rx=mx-(mx%5)-2;
            ry=my-(my%5)-2;
            qDebug() << mouseEvent->x() << " to " << rx;
            qDebug() << mouseEvent->y() << " to " << ry;
            rw = rh = 3+5*((int)star->getSize());
            mapScene->addRect(rx,ry,rw,rh,pen,Qt::NoBrush);
        }*/
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
    //fontString=label->font().family();
    fontString=mapFont.family();
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
    QFont newFont = mapFont;
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

void StarMapUI::addPlayerMarkers(){
    starMap->starListIterator=starMap->begin();
    QPen pen;
    pen.setWidth(1);
    int i=0;
    while (starMap->starListIterator!= starMap->end()){
        int ptx, pty, w, h;
        ptx=(*(starMap->starListIterator))->getX()*5-2;
        pty=(*(starMap->starListIterator))->getY()*5-2;
        rgb_t pcolor = getPlayerColor((*(starMap->starListIterator))->getOwner());
        pen.setColor(QColor::fromRgb(pcolor.r,pcolor.g,pcolor.b));
 //       qDebug() << mouseEvent->x() << " to " << rx;
//        qDebug() << mouseEvent->y() << " to " << ry;
        w = h = 3+5*((int)(*(starMap->starListIterator))->getSize());
//        mapScene->addRect(ptx,pty,w,h,pen,Qt::NoBrush);
        if ((*(starMap->starListIterator))->getSize()==DWARF){
            mapScene->addLine(ptx, pty, ptx+1, pty, pen);
            mapScene->addLine(ptx, pty, ptx, pty+1, pen);
            mapScene->addLine(ptx+w, pty, ptx+w-1, pty, pen);
            mapScene->addLine(ptx+w, pty, ptx+w, pty+1, pen);
            mapScene->addLine(ptx, pty+h, ptx+1, pty+h, pen);
            mapScene->addLine(ptx, pty+h, ptx, pty+h-1, pen);
            mapScene->addLine(ptx+w, pty+h, ptx+w-1, pty+h, pen);
            mapScene->addLine(ptx+w, pty+h, ptx+w, pty+h-1, pen);
        }
        else{
            mapScene->addLine(ptx, pty, ptx+2, pty, pen);
            mapScene->addLine(ptx, pty, ptx, pty+2, pen);
            mapScene->addLine(ptx+w, pty, ptx+w-2, pty, pen);
            mapScene->addLine(ptx+w, pty, ptx+w, pty+2, pen);
            mapScene->addLine(ptx, pty+h, ptx+2, pty+h, pen);
            mapScene->addLine(ptx, pty+h, ptx, pty+h-2, pen);
            mapScene->addLine(ptx+w, pty+h, ptx+w-2, pty+h, pen);
            mapScene->addLine(ptx+w, pty+h, ptx+w, pty+h-2, pen);
        }
/*        mapScene->addLine(ptx+1, pty+1, ptx, pty+2, pen);
        mapScene->addLine(ptx, pty+h-1, ptx+1, pty+h, pen);
        mapScene->addLine(ptx+h, pty+h, ptx+h-1, pty+h+1, pen);
        mapScene->addLine(ptx+h-1, pty, ptx+h, pty+1, pen);*/
        //qDebug() << i++;
        starMap->starListIterator++;
    }

}
