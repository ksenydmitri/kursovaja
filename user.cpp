#include "user.h"
#include <QDebug>

User::User()
    : nickname(""), password(""), avatarPath(""), backgroundPath(""), musicPath(""), difficulty(""), bestScore(0), attempts(5), lastAttemptTime(QDateTime::currentDateTime()) {}

User::User(const QString &nickname, const QString &password, const QString &avatarPath, const QString &backgroundPath, int bestScore)
    : nickname(nickname), password(password), avatarPath(avatarPath), backgroundPath(backgroundPath), musicPath(""), difficulty(""), bestScore(bestScore), attempts(5), lastAttemptTime(QDateTime::currentDateTime()) {}

QString User::getNickname() const {
    return nickname;
}

QString User::getPassword() const {
    return password;
}

QString User::getAvatarPath() const {
    return avatarPath;
}

QString User::getBackgroundPath() const {
    return backgroundPath;
}

QString User::getMusicPath() const {
    return musicPath;
}

QString User::getDifficulty() const {
    return difficulty;
}

int User::getBestScore() const {
    return bestScore;
}

void User::setAvatarPath(const QString &avatarPath) {
    this->avatarPath = avatarPath;
}

void User::setBackgroundPath(const QString &backgroundPath) {
    this->backgroundPath = backgroundPath;
    qDebug() << "Background path set to:" << backgroundPath;
}

void User::setMusicPath(const QString &musicPath) {
    this->musicPath = musicPath;
}

void User::setDifficulty(const QString &difficulty) {
    this->difficulty = difficulty;
}

void User::setBestScore(int score) {
    if (score > bestScore) {
        bestScore = score;
    }
}

int User::getAttempts() const {
    return attempts;
}

void User::setAttempts(int attempts) {
    this->attempts = attempts;
}

void User::decreaseAttempt() {
    if (attempts > 0) {
        attempts--;
        lastAttemptTime = QDateTime::currentDateTime();
    }
}

void User::restoreAttempt() {
    if (attempts < 5) {
        attempts++;
    }
}

QDateTime User::getLastAttemptTime() const {
    return lastAttemptTime;
}

void User::setLastAttemptTime(const QDateTime &time) {
    lastAttemptTime = time;
}
