#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

#include "HSLColorWheel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    QVBoxLayout vl1(&window);

    HSLColorWheel wheel(&window);

    vl1.addWidget(&wheel);

    window.setLayout(&vl1);

    //window.addWidget(wheel);

    window.show();
    return app.exec();
}
