#include "phase6_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Phase6_GUI w;
    w.show();

    return a.exec();
}
