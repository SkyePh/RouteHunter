//Std
#include <iostream>

//Qt
#include <QApplication>
#include <QIcon>

//Classes
#include "src/Platform.h"
#include "src/MainWindow.h"


using namespace std;

int main(int argc, char *argv[]) {
    cout << "Started RouteHunter" << endl;
    cout << "Detecting system archtitecure" << endl;

    string ffufPath = getFFUFPath();

    if (ffufPath.empty()) {
        cerr << "System not supported.\n Supported Systems:\n Linux, Windows, MacOS both ARM64 and AMD64\n";
        return 1;
    }

    cout << "Started route hunter" << endl;

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":/assets/RouteHunter.png")));

    MainWindow window;
    window.show();

    return app.exec();
}
