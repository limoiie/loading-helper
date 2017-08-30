#include "widget.h"
#include "AnimateHelper/material_loading_helper.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MaterialLoadingHelper *p_helper = new MaterialLoadingHelper(45*16, 225*16, 2000, 500, 2, {});

    Widget w(p_helper);
    w.show();

    w.move((QApplication::desktop()->width() - w.width())/2,
           (QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
