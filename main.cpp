#include <iostream>
#include "QApplication"
#include "Service.h"
#include "Gui.h"
int main(int argc, char ** argv) {
    QApplication app(argc, argv);
    FileRepository<Ethnologist> ethno("ethnologists.txt", "/Users/andreeaploscar/CLionProjects/e2-915-Ploscar-Andreea-c/");
    FileRepository<Building> buildings("buildings.txt", "/Users/andreeaploscar/CLionProjects/e2-915-Ploscar-Andreea-c/");
    Service service(buildings, ethno);
    Gui * gui = new Gui(service);
    return app.exec();
}