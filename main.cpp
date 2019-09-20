#include "Fullscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if(app.arguments().length() < 4)
        qFatal("Usage: %s INTERFACE UNIVERSE CHANNEL", app.arguments().first().toLocal8Bit().constData());

    auto interface = QNetworkInterface::interfaceFromName(app.arguments()[1]);
    if(!interface.isValid())
        qFatal("Invalid interface: %s", app.arguments()[1].toLocal8Bit().constData());

    QNetworkAddressEntry address; // first IPv4 address
    bool foundAddress = false;
    for(auto &addressEntry : interface.addressEntries()) {
        if(addressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
            address = addressEntry;
            foundAddress = true;
        }
    }
    if(!foundAddress)
        qFatal("Failed to find IPv4 address on interface");

    Fullscreen f(interface, address, app.arguments()[2].toUInt(), app.arguments()[3].toUInt());
    f.showFullScreen();

    return app.exec();
}
