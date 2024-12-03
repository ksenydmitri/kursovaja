#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QComboBox>
#include "usermanager.h"

// Базовый класс Setting
class Setting : public QObject {
    Q_OBJECT

public:
    explicit Setting(UserManager *userManager, QObject *parent = nullptr);
    virtual ~Setting();

    virtual void applySetting(const QString &username, const QString &value) = 0;

signals:
    void settingChanged(const QString &newValue);  // Объявление сигнала

protected:
    UserManager *userManager;
};

// Класс AvatarSetting
class AvatarSetting : public Setting {
    Q_OBJECT

public:
    explicit AvatarSetting(UserManager *userManager, QObject *parent = nullptr);
    void applySetting(const QString &username, const QString &value) override;
};

// Класс BackgroundSetting
class BackgroundSetting : public Setting {
    Q_OBJECT

public:
    explicit BackgroundSetting(UserManager *userManager, QObject *parent = nullptr);
    void applySetting(const QString &username, const QString &value) override;
};

// Класс MusicSetting
class MusicSetting : public Setting {
    Q_OBJECT

public:
    explicit MusicSetting(UserManager *userManager, QObject *parent = nullptr);
    void applySetting(const QString &username, const QString &value) override;
};

// Класс DifficultySetting
class DifficultySetting : public Setting {
    Q_OBJECT

public:
    explicit DifficultySetting(QComboBox *comboBox, UserManager *userManager, QObject *parent = nullptr);
    void applySetting(const QString &username, const QString &value) override;
    QString getSelectedDifficulty() const;

private:
    QComboBox *difficultyComboBox;
};

#endif // SETTINGS_H
