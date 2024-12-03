#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QString>

class Button : public QPushButton {
    Q_OBJECT

public:
    explicit Button(const QString &iconPath, QWidget *parent = nullptr);
    void setIconPath(const QString &iconPath);
    virtual ~Button(); // Виртуальный деструктор

private:
    QString iconPath;
};

class StartButton : public Button {
    Q_OBJECT

public:
    explicit StartButton(QWidget *parent = nullptr);
    virtual ~StartButton(); // Виртуальный деструктор
};

class ReturnButton : public Button {
    Q_OBJECT

public:
    explicit ReturnButton(QWidget *parent = nullptr);
    virtual ~ReturnButton(); // Виртуальный деструктор
};

class SettingsButton : public Button {
    Q_OBJECT

public:
    explicit SettingsButton(QWidget *parent = nullptr);
    virtual ~SettingsButton(); // Виртуальный деструктор
};

class LogoutButton : public Button {
    Q_OBJECT

public:
    explicit LogoutButton(QWidget *parent = nullptr);
    virtual ~LogoutButton(); // Виртуальный деструктор
};

class FreezeButton : public Button {
    Q_OBJECT

public:
    explicit FreezeButton(QWidget *parent = nullptr);
    virtual ~FreezeButton(); // Виртуальный деструктор
};

class ChangeAvatarButton : public SettingsButton {
    Q_OBJECT

public:
    explicit ChangeAvatarButton(QWidget *parent = nullptr);
    virtual ~ChangeAvatarButton(); // Виртуальный деструктор
};

class ChangeMusicButton : public SettingsButton {
    Q_OBJECT

public:
    explicit ChangeMusicButton(QWidget *parent = nullptr);
    virtual ~ChangeMusicButton(); // Виртуальный деструктор
};

class ChangeBackgroundButton : public SettingsButton {
    Q_OBJECT

public:
    explicit ChangeBackgroundButton(QWidget *parent = nullptr);
    virtual ~ChangeBackgroundButton(); // Виртуальный деструктор
};

#endif // BUTTON_H
