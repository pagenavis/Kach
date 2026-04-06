#include <QCoreApplication>
#include <QDebug>
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Создаём объект сервера
    Server server;

    return a.exec();
}
