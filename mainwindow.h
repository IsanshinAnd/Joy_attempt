#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <SDL2/SDL.h>
#undef main

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum HatPosition {
        JOYSTICK_HAT_CENTERED,
        JOYSTICK_HAT_UP,
        JOYSTICK_HAT_UP_RIGHT,
        JOYSTICK_HAT_RIGHT,
        JOYSTICK_HAT_DOWN_RIGHT,
        JOYSTICK_HAT_DOWN,
        JOYSTICK_HAT_DOWN_LEFT,
        JOYSTICK_HAT_LEFT,
        JOYSTICK_HAT_UP_LEFT
    };


private:
    Ui::MainWindow *ui;
    SDL_Joystick *joy;
    QTimer timer;
    QVector<bool> buttonVector;
    static HatPosition convertHatPosition(int position);
    QString getHatsPosition(int pos);

signals:
    void sigButtonChanged(int id, bool state);
    void sigAxisChanged(int id, int state);
    void sigHatCanged(int id, int state);

private slots:
    void onTimer();
    void axisSetup(int id, int state);
    void hatSetup(int id, int state);
    void buttonSetup(int id, bool state);

};

#endif // MAINWINDOW_H
