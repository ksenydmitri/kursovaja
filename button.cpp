#include "button.h"
#include <QPixmap>

Button::Button(const QString &iconPath, QWidget *parent) : QPushButton(parent), iconPath(iconPath) {
    setIcon(QIcon(QPixmap(iconPath)));
    setStyleSheet("QPushButton { background-color: transparent; }");
}

void Button::setIconPath(const QString &iconPath) {
    this->iconPath = iconPath;
    setIcon(QIcon(QPixmap(iconPath)));
}

Button::~Button() {}

StartButton::StartButton(QWidget *parent) : Button("startgame.png", parent) {
    setFixedSize(150, 100);
    setIconSize(size());
}

StartButton::~StartButton() {}

ReturnButton::ReturnButton(QWidget *parent) : Button("return.png", parent) {
    setFixedSize(150, 100);
    setIconSize(size());
}

ReturnButton::~ReturnButton() {}

SettingsButton::SettingsButton(QWidget *parent) : Button("settings.png", parent) {
    setFixedSize(40, 40);
    setIconSize(size());
}

SettingsButton::~SettingsButton() {}

LogoutButton::LogoutButton(QWidget *parent) : Button("logout.png", parent) {
    setFixedSize(50, 50);
    setIconSize(size());
}

LogoutButton::~LogoutButton() {}

FreezeButton::FreezeButton(QWidget *parent) : Button("freeze.png", parent) {
    setFixedSize(40, 40);
    setIconSize(size());
}

FreezeButton::~FreezeButton() {}

ChangeAvatarButton::ChangeAvatarButton(QWidget *parent) : SettingsButton(parent) {
    setFixedSize(150, 50);
    setText("Изменить аватар");
    setStyleSheet( "QPushButton { background-image: url(button.png);}");
    Button::setIconPath("default_avatar.jpg");
}

ChangeAvatarButton::~ChangeAvatarButton() {}

ChangeMusicButton::ChangeMusicButton(QWidget *parent) : SettingsButton(parent) {
    setFixedSize(150, 50);
    setText("Изменить музыку");
    setStyleSheet( "QPushButton { background-image: url(button.png);}");
    Button::setIconPath("default_avatar.jpg");
}

ChangeMusicButton::~ChangeMusicButton() {}

ChangeBackgroundButton::ChangeBackgroundButton(QWidget *parent) : SettingsButton(parent) {
    setFixedSize(150, 50);
    setText("Изменить фон");
    setStyleSheet( "QPushButton { background-image: url(button.png);}");
}

ChangeBackgroundButton::~ChangeBackgroundButton() {}
