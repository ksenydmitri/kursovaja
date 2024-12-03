#include "settings.h"
#include <QFileDialog>
#include <QDebug>

Setting::Setting(UserManager *userManager, QObject *parent) : QObject(parent), userManager(userManager) {
}

Setting::~Setting() {}

AvatarSetting::AvatarSetting(UserManager *userManager, QObject *parent) : Setting(userManager, parent) {
}

void AvatarSetting::applySetting(const QString &username, const QString &value) {

    if (!userManager) {
        qDebug() << "UserManager is null";
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(qobject_cast<QWidget*>(parent()), "Выберите аватар", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        userManager->updateUserAvatar(username, filePath);
        userManager->saveUsersToFile("users.txt");
        emit settingChanged(filePath);
    }
}



BackgroundSetting::BackgroundSetting(UserManager *userManager, QObject *parent) : Setting(userManager, parent) {}

void BackgroundSetting::applySetting(const QString &username, const QString &value) {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выберите фон", "", "Images (*.png *.jpg *.bmp)"); 
    if (!filePath.isEmpty()) {
        bool updated = userManager->updateUserBackground(username, filePath);
        if (updated) {
            userManager->saveUsersToFile("users.txt");
            emit settingChanged(filePath);
        } else {
            qDebug() << "updateUserBackground failed for user:" << username;
        }
    } else {
        qDebug() << "No file selected";
    }
}

MusicSetting::MusicSetting(UserManager *userManager, QObject *parent) : Setting(userManager, parent) {}

void MusicSetting::applySetting(const QString &username, const QString &value) {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выберите музыку", "", "Audio Files (*.mp3 *.wav)");
    if (!filePath.isEmpty()) {
        userManager->updateUserMusic(username, filePath);
        userManager->saveUsersToFile("users.txt");
        emit settingChanged(filePath);
    }
}

DifficultySetting::DifficultySetting(QComboBox *comboBox, UserManager *userManager, QObject *parent)
    : Setting(userManager, parent), difficultyComboBox(comboBox) {}

void DifficultySetting::applySetting(const QString &username, const QString &value) {
    QString selectedDifficulty = difficultyComboBox->currentText();
    userManager->updateUserDifficulty(username, selectedDifficulty);
    userManager->saveUsersToFile("users.txt");
    emit settingChanged(selectedDifficulty);
}

QString DifficultySetting::getSelectedDifficulty() const {
    return difficultyComboBox->currentText();
}
