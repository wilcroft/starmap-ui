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
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QBrush>
#include <QPen>

#include "cli_tools/map.h"
#include "cli_tools/star.h"
#include "cli_tools/util.h"

namespace Ui {
class StarMapUI;
}
class StarMapUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit StarMapUI(QWidget *parent = 0);
    ~StarMapUI();

protected:
//    void mouseMoveEvent(QMouseEvent* event);
    bool eventFilter(QObject *, QEvent *);
    void setScaledText(QLabel* label, QString text, int maxpt=16);
    void clearSidebar();
    void addPlayerMarkers();

private slots:
    void newMap();

    void openMap();

    void exitApp();

private:
    Ui::StarMapUI *ui;
    QGraphicsScene* mapScene;
    QGraphicsPixmapItem* mapItem;
    QGraphicsView* mapView;

    QGraphicsScene* starScene;
    QGraphicsPixmapItem* starItem;
    QGraphicsScene* planetScene[5];
    QGraphicsPixmapItem* planetItem[5];

    QLabel* planetLabelPtr [5];
    QGraphicsView* planetViewPtr [5];

    Map* starMap;
    bool mapExists;
    int count;

};

#endif // STARMAPUI_H
