#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include "gamelogic.h"
#include "button.h"
#include "settings.h"
#include "lable.h"

class BaseWidget : public QWidget {
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = nullptr);
    virtual void setBackground(const QString& imagePath) = 0;

protected:
    QVBoxLayout *layout;
};

class MenuWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr, UserManager *userManager = nullptr, const User &currentUser = User());
    void setBackground(const QString& imagePath) override;
    void updateUser(const User &user);
    void updateBestScore();
    void updateAvatar(const QString &avatarPath);
    void updateAttempts();

signals:
    void startGame();
    void openSettings();
    void logout();

private:
    AttemptsLabel *attemptsLabel;
    AttemptsImage *attemptsImage;
    TimerLabel *timerLabel;
    BestScoreLabel *bestScoreLabel;
    AvatarWidget *avatarLabel;
    UserManager *userManager;
    User currentUser;
};

class SettingsWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    void setBackground(const QString& imagePath) override;
    void setUserManager(UserManager *userManager);
    void setCurrentUser(const QString &username);

signals:
    void backToMenu();
    void backgroundChanged(const QString &imagePath);
    void avatarChanged(const QString &filePath);
    void musicChanged(const QString &filePath);
    void difficultyChanged(const QString &difficulty);

private slots:
    void onChangeAvatarClicked();
    void onChangeBackgroundClicked();
    void onChangeMusicClicked();
    void onDifficultyChanged(int index);

private:
    ChangeAvatarButton *changeAvatarButton;
    ChangeBackgroundButton *changeBackgroundButton;
    QPushButton *changeMusicButton;
    QPushButton *backButton;
    QComboBox *difficultyComboBox;

    AvatarSetting *avatarSetting;
    BackgroundSetting *backgroundSetting;
    MusicSetting *musicSetting;
    DifficultySetting *difficultySetting;

    QString currentUsername;
    UserManager *userManager;
};

class GameOverWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit GameOverWidget(QWidget *parent = nullptr);
    void setBackground(const QString& imagePath) override;

signals:
    void playAgain();
    void returnToMenu();

private slots:
    void onPlayAgainButtonClicked();
    void onReturnButtonClicked();

private:
    QLabel *gameOverLabel;
    QPushButton *playAgainButton;
    QPushButton *returnButton;
};

class GameWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr, UserManager *userManager = nullptr, const User &currentUser = User());
    void updateUser(const User &user);
    void updateBackground(const QString& imagePath);
    void setBackground(const QString& imagePath) override;
    void updateScore(int score);
    void increaseScore();
    QLabel *scoreLabel;
    int currentScore;

public slots:
    void startGame();
    void setDifficulty(const QString &difficulty);

signals:
    void backToMenu();
    void gameEnded();
    void attemptsChanged(int attempts);

private slots:
    void onGameEnded();
private:
    UserManager *userManager;
    User currentUser;
    GameLogic *gameLogic;
    QPushButton *backButton;


    void resetGame();
    void updateScoreLabel(); // Новый метод для обновления этикетки счета
    void checkAndUpdateBestScore(); // Новый метод для проверки и сохранения лучшего счета
};

#endif // BASEWIDGET_H
