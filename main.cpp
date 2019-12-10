#include "phase6_gui.h"
#include <QApplication>
#include <QString>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Phase6_GUI w;
    w.show();


//    QString path = QCoreApplication::applicationDirPath();
//    QFile* file = new QFile(path + "/vocab.voc");


//    QTextStream in(file);

//    while (!in.atEnd()) {

//        QString line = in.readLine();
//        QStringList fields = line.split(";");

//    }

    return a.exec();
}
