#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVector>
#include <QString>
#include <QStringList>
#undef main

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_EVENTS);
    SDL_JoystickEventState(SDL_ENABLE);

    joy = SDL_JoystickOpen(0);

    connect(this, SIGNAL(sigButtonChanged(int, bool)), this, SLOT(buttonSetup(int,bool)));
    connect(this, SIGNAL(sigAxisChanged(int,int)), this, SLOT(axisSetup(int,int)));
    connect(this, SIGNAL(sigHatCanged(int,int)), this, SLOT(hatSetup(int,int)));
    connect(ui->exitPushButton, SIGNAL(clicked()), this, SLOT(close()));

    buttonVector.fill(false);

    ui->joystickNameLabel->setText(SDL_JoystickName(joy));
    ui->joystickIdLabel->setText(QString::number(SDL_JoystickInstanceID(joy)));
    ui->joystickAxisLabel->setText(QString::number(SDL_JoystickNumAxes(joy)));
    ui->joystickHatsLabel->setText(QString::number(SDL_JoystickNumHats(joy)));
    ui->joystickBallsLabel->setText(QString::number(SDL_JoystickNumBalls(joy)));
    ui->joystickButtonsLabel->setText(QString::number(SDL_JoystickNumButtons(joy)));

    ui->joystickStateBox->setEnabled(true);
    ui->joystickInformationBox->setEnabled(true);
    ui->joystickComboBox->setDisabled(true);

    timer.setInterval(50);
    timer.start();

}

MainWindow::~MainWindow()
{   SDL_Quit();
    delete ui;
}

void MainWindow::onTimer()
{
    SDL_Event joyEvent;
    while (SDL_PollEvent(&joyEvent))
    {
        switch (joyEvent.type)
        {
            case SDL_JOYAXISMOTION:
                emit sigAxisChanged(joyEvent.jaxis.axis,joyEvent.jaxis.value);
                break;
            case SDL_JOYHATMOTION:
                emit sigHatCanged(joyEvent.jhat.hat, MainWindow::convertHatPosition(joyEvent.jhat.value));
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                emit sigButtonChanged(joyEvent.jbutton.button, joyEvent.jbutton.state);
                break;
            default: break;
        }
    }
}

MainWindow::HatPosition MainWindow::convertHatPosition(int position)
{
    switch(position) {
    case SDL_HAT_CENTERED:
        return JOYSTICK_HAT_CENTERED;
        break;

    case SDL_HAT_UP:
        return JOYSTICK_HAT_UP;
        break;

    case SDL_HAT_RIGHTUP:
        return JOYSTICK_HAT_UP_RIGHT;
        break;

    case SDL_HAT_RIGHT:
        return JOYSTICK_HAT_RIGHT;
        break;

    case SDL_HAT_RIGHTDOWN:
        return JOYSTICK_HAT_DOWN_RIGHT;
        break;

    case SDL_HAT_DOWN:
        return JOYSTICK_HAT_DOWN;
        break;
    case SDL_HAT_LEFTDOWN:
        return JOYSTICK_HAT_DOWN_LEFT;
        break;

    case SDL_HAT_LEFT:
        return JOYSTICK_HAT_LEFT;
        break;

    case SDL_HAT_LEFTUP:
        return JOYSTICK_HAT_UP_LEFT;
        break;

    default:
        return JOYSTICK_HAT_CENTERED;
        break;
    }
    return JOYSTICK_HAT_CENTERED;
}

void MainWindow::axisSetup(int id, int state)
{
    switch(id)
    {
    case 0:
        ui->joystickXaxisLabel->setText(QString::number(state));
        break;
    case 1:
        ui->joystickYaxisLabel->setText(QString::number(-1*state));
        break;
    case 2:
        ui->joystickZLTaxisLabel->setText(QString::number(state));
        break;
    case 3:
        ui->joystickXrotationLabel->setText(QString::number(state));
        break;
    case 4:
        ui->joystickYrotationLabel->setText(QString::number(-1*state));
        break;
    case 5:
        ui->joystickZRTaxisLabel->setText(QString::number(state));
        break;
    }
}
void MainWindow::hatSetup(int id, int state)
{
    Q_UNUSED(id);
    ui->joystickPOV0Label->setText(getHatsPosition(state));
}
void MainWindow::buttonSetup(int id, bool state)
{
    buttonVector[id] = state;

    QString buttonTest = "";
    for(int i = 0; i < 30; ++i)
    {
        if(buttonVector[i] == true)
        {
            if(i < 10)
                buttonTest += tr("0%1  ").arg(i);
            else
                buttonTest += tr("%1").arg(i);
        }
    }
    ui->joystickButtonsTestLabel->setText(buttonTest);
}

QString MainWindow::getHatsPosition(int pos)
{
    QString text("");

    switch(pos) {
    case JOYSTICK_HAT_CENTERED:
        text += "centre";
        break;

    case JOYSTICK_HAT_UP:
        text += "up";
        break;

    case JOYSTICK_HAT_UP_RIGHT:
        text += "up right";
        break;

    case JOYSTICK_HAT_RIGHT:
        text += "right";
        break;

    case JOYSTICK_HAT_DOWN_RIGHT:
        text += "right down";
        break;

    case JOYSTICK_HAT_DOWN:
        text += "down";
        break;

    case JOYSTICK_HAT_DOWN_LEFT:
        text += "down left";
        break;

    case JOYSTICK_HAT_LEFT:
        text += "left";
        break;

    case JOYSTICK_HAT_UP_LEFT:
        text += "left up";
        break;
    }
    return text;
}
