#include "mainwindow.h"
#include <QDebug>
#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentUser() {
    qDebug() << "MainWindow constructor called";

    setFixedSize(400, 600);

    userManager.loadUsersFromFile("users.txt");

    stackedWidget = new QStackedWidget(this);
    menuWidget = new MenuWidget(this, &userManager, currentUser);
    gameWidget = new GameWidget(this, &userManager, currentUser);
    settingsWidget = new SettingsWidget(this);
    gameOverWidget = new GameOverWidget(this);

    if (settingsWidget == nullptr) {
        qDebug() << "Failed to create SettingsWidget";
    } else {
        qDebug() << "SettingsWidget created successfully";
    }

    settingsWidget->setUserManager(&userManager);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);
    stackedWidget->addWidget(settingsWidget);
    stackedWidget->addWidget(gameOverWidget);

    setCentralWidget(stackedWidget);

    connect(menuWidget, &MenuWidget::startGame, gameWidget, &GameWidget::startGame);
    connect(menuWidget, &MenuWidget::startGame, this, [this]() {
        switchWidget(menuWidget, gameWidget);
        setWidgetBackground(gameWidget, gameBackgroundPath);
    });

    connect(menuWidget, &MenuWidget::openSettings, this, [this]() {
        switchWidget(menuWidget, settingsWidget);
    });

    connect(gameWidget, &GameWidget::backToMenu, this, [this]() {
        switchWidget(gameWidget, menuWidget);
    });

    connect(gameWidget, &GameWidget::gameEnded, this, &MainWindow::showGameOverWidget);
    //connect(gameWidget, &GameWidget::gameStarted, this, &MainWindow::restoreAttempt);

    connect(gameOverWidget, &GameOverWidget::returnToMenu, this, [this]() {
        switchWidget(gameOverWidget, menuWidget);
    });

    connect(gameOverWidget, &GameOverWidget::playAgain, gameWidget, &GameWidget::startGame);
    connect(gameOverWidget, &GameOverWidget::playAgain, this, [this]() {
        switchWidget(gameOverWidget, gameWidget);
    });

    connect(settingsWidget, &SettingsWidget::backToMenu, this, [this]() {
        switchWidget(settingsWidget, menuWidget);
    });

    // Соединение сигналов из SettingsWidget со слотами в MainWindow
    connect(settingsWidget, &SettingsWidget::avatarChanged, this, &MainWindow::onAvatarChanged);
    connect(settingsWidget, &SettingsWidget::backgroundChanged, this, &MainWindow::onBackgroundChanged);
    connect(settingsWidget, &SettingsWidget::musicChanged, this, &MainWindow::onMusicChanged);
    connect(settingsWidget, &SettingsWidget::difficultyChanged, this, &MainWindow::onDifficultyChanged);

    // Создаем и запускаем таймер для восстановления попыток
    restoreTimer = new QTimer(this);
    connect(restoreTimer, &QTimer::timeout, this, &MainWindow::restoreAttempt);
    restoreTimer->start(60000); // Интервал 1 минута

    connect(gameWidget, &GameWidget::attemptsChanged, menuWidget, &MenuWidget::updateAttempts);

    stackedWidget->setCurrentWidget(menuWidget);

    LoginWindow *loginWindow = new LoginWindow(this, &userManager);
    connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSuccess);
    if (loginWindow->exec() != QDialog::Accepted) {
        close();
        return;
    }
    connect(menuWidget, &MenuWidget::logout, this, &MainWindow::logoutUser);
}

void MainWindow::switchWidget(BaseWidget *currentWidget, BaseWidget *newWidget) {
    stackedWidget->setCurrentWidget(newWidget);
}

void MainWindow::setWidgetBackground(BaseWidget *widget, const QString &imagePath) {
    if (!imagePath.isEmpty()) {
        widget->setBackground(imagePath);
    }
}

void MainWindow::onLoginSuccess(const User &user) {
    currentUser = user;
    gameBackgroundPath = user.getBackgroundPath();
    settingsWidget->setCurrentUser(user.getNickname());
    menuWidget->updateUser(currentUser);
    menuWidget->update();
    gameWidget->updateUser(currentUser);
    gameWidget->update();

    QDateTime currentTime = QDateTime::currentDateTime();
    int minutesPassed = currentUser.getLastAttemptTime().secsTo(currentTime) / 60;
    if (minutesPassed > 0) {
        int attemptsToRestore = qMin(minutesPassed, 5 - currentUser.getAttempts());
        for (int i = 0; i < attemptsToRestore; ++i) {
            currentUser.restoreAttempt();
        }
        userManager.updateAttempts(currentUser.getNickname(), currentUser.getAttempts());
        menuWidget->updateAttempts(); // Обновляем отображение попыток
    }
}

void MainWindow::showGameOverWidget() {
    switchWidget(gameWidget, gameOverWidget);
    menuWidget->updateBestScore();
    menuWidget->update();
}

void MainWindow::logoutUser() {
    if (!currentUser.getNickname().isEmpty()) {
        userManager.saveUsersToFile("users.txt");
    }
    currentUser = User();
    LoginWindow *loginWindow = new LoginWindow(this, &userManager);
    connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSuccess);
    if (loginWindow->exec() != QDialog::Accepted) {
        close();
        return;
    }
    qDebug() << "User logged out";
    onLoginSuccess(currentUser); // Обновляем интерфейс после выхода пользователя
}

void MainWindow::onAvatarChanged(const QString &filePath) {
    qDebug() << "Avatar changed to" << filePath;
    menuWidget->updateAvatar(filePath);
}

void MainWindow::onBackgroundChanged(const QString &filePath) {
    qDebug() << "Background changed to" << filePath;
    setWidgetBackground(menuWidget, filePath);
    setWidgetBackground(gameWidget, filePath);
}

void MainWindow::onMusicChanged(const QString &filePath) {
    qDebug() << "Music changed to" << filePath;
    // Обработка изменения музыки
}

void MainWindow::onDifficultyChanged(const QString &difficulty) {
    qDebug() << "Difficulty changed to" << difficulty;
    gameWidget->setDifficulty(difficulty);
}

void MainWindow::restoreAttempt() {
    if (!currentUser.getNickname().isEmpty() && currentUser.getAttempts() < 5) {
        currentUser.restoreAttempt();
        userManager.updateAttempts(currentUser.getNickname(), currentUser.getAttempts());
        menuWidget->updateAttempts(); // Обновляем отображение попыток
        qDebug() << "Attempt restored. Current attempts:" << currentUser.getAttempts();
    }
}
