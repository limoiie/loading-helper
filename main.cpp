#include "widget.h"
 #include "AnimateHelper/material_loading_helper.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Helper *p_helper = (new MaterialLoadingHelper::MaterialLoadingBuilder())
            ->setClockwise(true)
            ->setMaxLen(225*16)
            ->setMinLen(45*16)
            ->setPeriod(1200, 100)
            ->setSpeed(2)
            ->setColorList({})
            ->build();

    Widget w(p_helper);
    w.show();

    w.move((QApplication::desktop()->width() - w.width())/2,
           (QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
