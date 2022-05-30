#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <QApplication>
#include "UIAtom.h"

int WinMain(int argc, char *argv[]) {
    QApplication a(argc, argv);
    UIAtom atom;

    atom.show();
    return a.exec();
}
