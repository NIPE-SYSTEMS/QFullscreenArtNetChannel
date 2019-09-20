#pragma once

#include <QWidget>

class Fullscreen : public QWidget
{
    Q_OBJECT

public:
    Fullscreen(QWidget *parent = nullptr);
    ~Fullscreen() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
