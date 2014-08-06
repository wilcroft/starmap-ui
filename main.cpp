#define ISCLI 0
#include "starmapui.h"
#include <QApplication>

int userDim;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StarMapUI w;
    w.show();

    return a.exec();
}
