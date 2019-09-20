#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QWidget>

class Fullscreen : public QWidget
{
    Q_OBJECT

public:
    Fullscreen(QWidget *parent = nullptr);
    ~Fullscreen();
};
#endif // FULLSCREEN_H
