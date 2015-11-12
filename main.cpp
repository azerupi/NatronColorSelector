#include <QApplication>
#include <QWidget>

#include "ColorWheel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    ColorWheel wheel(&window);

    //window.addWidget(wheel);

    window.show();
    return app.exec();
}
