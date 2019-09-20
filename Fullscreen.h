#pragma once

#include <QWidget>

#include "qlcplus/plugins/artnet/src/artnetcontroller.h"

class Fullscreen : public QWidget
{
    Q_OBJECT

    QSharedPointer<QUdpSocket> socket;
    ArtNetController *controller;
    uint channelOffset;
    QColor color;
    bool invalidate;

public:
    Fullscreen(const QNetworkInterface &interface, const QNetworkAddressEntry &address, quint32 universe, quint32 channelOffset, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void readyRead();
    void valueChanged(quint32 universe, quint32 input, quint32 channelOffset, uchar value);
};
