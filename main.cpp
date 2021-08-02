#include "ToDoApps.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToDoApps w;
    w.show();
    return a.exec();
}
