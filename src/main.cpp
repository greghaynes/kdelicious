#include <QCoreApplication>
#include "kdelicious.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    kdelicious foo;
    return app.exec();
}
