#include <QApplication>
#include <QWidget>
#include <QFile>


#include "Window.h"

int main( int argc, char * argv[])
{
    QApplication app(argc, argv);
    QFile File("../Style.qss");
     File.open(QFile::ReadOnly);
     QString StyleSheet = QLatin1String(File.readAll());

    qApp->setStyleSheet(StyleSheet);

    Window window;
    window.show();

    return app.exec();

}
