#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
public:
    User();
    User(const QString &nickname, const QString &password, const QString &avatarPath, const QString &backgroundPath, int bestScore);

    QString getNickname() const;
    QString getPassword() const;
    QString getAvatarPath() const;
    QString getBackgroundPath() const;
    QString getMusicPath() const;
    QString getDifficulty() const;
    int getBestScore() const;

    void setAvatarPath(const QString &avatarPath);
    void setBackgroundPath(const QString &backgroundPath);
    void setMusicPath(const QString &musicPath);
    void setDifficulty(const QString &difficulty);
    void setBestScore(int score);

    int getAttempts() const;
    void setAttempts(int attempts);
    void decreaseAttempt();
    void restoreAttempt();
    QDateTime getLastAttemptTime() const;
    void setLastAttemptTime(const QDateTime &time);

private:
    QString nickname;
    QString password;
    QString avatarPath;
    QString backgroundPath;
    QString musicPath;
    QString difficulty;
    int bestScore;
    int attempts;
    QDateTime lastAttemptTime; // Время последней попытки
};

#endif // USER_H
