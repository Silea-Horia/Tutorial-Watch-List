#include <QApplication>
#include <QScreen>
#include "repository/database.h"
#include "services/services.h"
#include "services/userservices.h"
#include "ui/GUI.h"
#include "services/writer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto* database = new Database;
    auto* csvWriter = new CSVWriter;
    auto* htmlWriter = new HTMLWriter;
    auto* services = new Services(database);
    auto* userServices = new UserServices(database, csvWriter, htmlWriter);
    QScreen* screen = a.primaryScreen();
    GUI gui(*database, *services, *userServices, screen);
    gui.show();
    return QApplication::exec();
}
