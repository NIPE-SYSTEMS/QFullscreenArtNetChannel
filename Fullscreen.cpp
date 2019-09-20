#include "Fullscreen.h"

#include <QPainter>

Fullscreen::Fullscreen(const QNetworkInterface &interface, const QNetworkAddressEntry &address, quint32 universe, quint32 channel, QWidget *parent) :
    QWidget(parent),
    channelOffset(channel),
    color(0, 0, 0)
{
    socket = QSharedPointer<QUdpSocket>(new QUdpSocket());
    if(!socket->bind(ARTNET_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
        qFatal("Failed to bind: 0:%d", ARTNET_PORT);
    connect(socket.data(), &QUdpSocket::readyRead, this, &Fullscreen::readyRead);

    controller = new ArtNetController(interface, address, socket, 0 /*line*/, this);
    controller->addUniverse(universe, ArtNetController::Input);
    connect(controller, &ArtNetController::valueChanged, this, &Fullscreen::valueChanged);
}

void Fullscreen::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
    painter.fillRect(rect(), color);
}

void Fullscreen::readyRead() {
    QByteArray datagram;
    QHostAddress senderAddress;

    invalidate = false;

    while(socket->hasPendingDatagrams()) {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &senderAddress);
        controller->handlePacket(datagram, senderAddress);
    }

    if(invalidate)
        update();
}

void Fullscreen::valueChanged(quint32 /*universe*/, quint32 /*input*/, quint32 channel, uchar value) {
    if(channel >= channelOffset && channel < channelOffset + 3) {
        switch(channel - channelOffset) {
        case 0: color.setRed(value);   break;
        case 1: color.setGreen(value); break;
        case 2: color.setBlue(value);  break;
        }

        invalidate = true;
    }
}
