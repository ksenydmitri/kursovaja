#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include <QMap>
#include <QString>
#include <QFile>
#include <QTextStream>

class UserManager {
public:
    UserManager();
    ~UserManager();

    bool addUser(const QString &nickname, const QString &password, const QString &avatarPath, const QString &backgroundPath);
    bool authenticate(const QString &nickname, const QString &password) const;
    User getUser(const QString &nickname) const;
    QString getBackground(const QString &nickname) const;

    void saveUsersToFile(const QString &filePath);
    void loadUsersFromFile(const QString &filePath);

    bool updateBestScore(const QString &nickname, int newBestScore);
    bool updateUserAvatar(const QString &nickname, const QString &avatarPath);
    bool updateUserBackground(const QString &nickname, const QString &backgroundPath);
    bool updateUserMusic(const QString &nickname, const QString &musicPath);
    bool updateUserDifficulty(const QString &nickname, const QString &difficulty);
    bool updateAttempts(const QString &nickname, int attempts);  // Новый метод для обновления попыток

    QMap<QString, User>& getUsers();

private:
    QMap<QString, User> users;
};

#endif // USERMANAGER_H
