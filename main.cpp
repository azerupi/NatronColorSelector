#include <QApplication>
#include <QWidget>

#include "HSLColorWheel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    HSLColorWheel wheel(&window);

    //window.addWidget(wheel);

    window.show();
    return app.exec();
}
