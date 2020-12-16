#include <QApplication>
#include "Models/Application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application app;
    app.start();
}
