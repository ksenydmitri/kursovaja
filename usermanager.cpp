#include "usermanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

UserManager::UserManager() {
    //loadUsersFromFile("users.txt");
}

UserManager::~UserManager() {}

bool UserManager::addUser(const QString &nickname, const QString &password, const QString &avatarPath, const QString &backgroundPath) {
    if (users.contains(nickname)) {
        return false;
    }
    User user(nickname, password, avatarPath, backgroundPath, 0);
    users.insert(nickname, user);
    saveUsersToFile("users.txt");
    return true;
}

bool UserManager::authenticate(const QString &nickname, const QString &password) const {
    qDebug() << "Checking if users contains nickname:" << nickname;
    if (!users.contains(nickname)) {
        qDebug() << "User not found:" << nickname;
        return false;
    }
    qDebug() << "User found. Checking password.";
    bool authenticated = (users[nickname].getPassword() == password);
    qDebug() << "Authentication" << (authenticated ? "successful" : "failed") << "for user:" << nickname;
    return authenticated;
}

User UserManager::getUser(const QString &nickname) const {
    if (!users.contains(nickname)) {
        qDebug() << "User not found in getUser:" << nickname;  // Отладочное сообщение
        return User();  // Возвращаем пустого пользователя или обрабатываем ошибку
    }
    return users.value(nickname);
}

QString UserManager::getBackground(const QString &nickname) const {
    if (!users.contains(nickname)) {
        return QString();
    }
    return users[nickname].getBackgroundPath();
}

void UserManager::saveUsersToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open" << filePath << "for writing";
        return;
    }
    QTextStream out(&file);
    for (const auto &user : users) {
        qDebug() << user.getNickname() << "," << user.getPassword() << "," << user.getAvatarPath() << "," << user.getBackgroundPath() << "," << user.getBestScore() << "," << user.getAttempts() << "," << user.getLastAttemptTime().toString(Qt::ISODate) << "\n";
        out << user.getNickname() << "," << user.getPassword() << "," << user.getAvatarPath() << "," << user.getBackgroundPath() << "," << user.getBestScore() << "," << user.getAttempts() << "," << user.getLastAttemptTime().toString(Qt::ISODate) << "\n";
    }
    file.close();
}

void UserManager::loadUsersFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open" << filePath << "for reading";
        return;
    }
    QTextStream in(&file);
    users.clear();
    int lineNumber = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        lineNumber++;
        QStringList parts = line.split(",");
        if (parts.size() == 7) {
            User user(parts[0], parts[1], parts[2], parts[3], parts[4].toInt());
            user.setAttempts(parts[5].toInt());
            user.setLastAttemptTime(QDateTime::fromString(parts[6], Qt::ISODate));
            users.insert(parts[0], user);
        } else {
            qDebug() << "Skipping malformed line" << lineNumber << ":" << line;
        }
    }
    file.close();
}

bool UserManager::updateBestScore(const QString &nickname, int newBestScore) {
    if (!users.contains(nickname)) {
        return false;
    }
    if (users[nickname].getBestScore() < newBestScore) {
        users[nickname].setBestScore(newBestScore);
        saveUsersToFile("users.txt");
        return true;
    }
    return false;
}

bool UserManager::updateUserAvatar(const QString &nickname, const QString &avatarPath) {
    if (!users.contains(nickname)) {
        return false;
    }
    users[nickname].setAvatarPath(avatarPath);
    saveUsersToFile("users.txt");
    return true;
}

bool UserManager::updateUserBackground(const QString &nickname, const QString &backgroundPath) {
    qDebug() << "Updating background for user:" << nickname << "with path:" << backgroundPath;
    if (!users.contains(nickname)) {
        qDebug() << "User not found:" << nickname;
        return false;
    }
    users[nickname].setBackgroundPath(backgroundPath);
    saveUsersToFile("users.txt");
    return true;
}

bool UserManager::updateUserMusic(const QString &nickname, const QString &musicPath) {
    if (!users.contains(nickname)) {
        return false;
    }
    users[nickname].setMusicPath(musicPath);
    saveUsersToFile("users.txt");
    return true;
}

bool UserManager::updateUserDifficulty(const QString &nickname, const QString &difficulty) {
    if (!users.contains(nickname)) {
        return false;
    }
    users[nickname].setDifficulty(difficulty);
    saveUsersToFile("users.txt");
    return true;
}

bool UserManager::updateAttempts(const QString &nickname, int attempts) {
    if (!users.contains(nickname)) {
        return false;
    }
    users[nickname].setAttempts(attempts);
    saveUsersToFile("users.txt");
    return true;
}

QMap<QString, User>& UserManager::getUsers() {
    return users;
}
