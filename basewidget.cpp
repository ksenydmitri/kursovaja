#include "basewidget.h"

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    setLayout(layout);
    setFixedSize(400, 600);
}

void BaseWidget::setBackground(const QString& imagePath) {
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(imagePath).scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    setAutoFillBackground(true);
    setPalette(palette);
}

MenuWidget::MenuWidget(QWidget *parent, UserManager *userManager, const User &currentUser)
    : BaseWidget(parent), userManager(userManager), currentUser(currentUser) {
    StartButton *gameButton = new StartButton(this);
    SettingsButton *settingsButton = new SettingsButton(this);
    attemptsLabel = new AttemptsLabel(this);
    AttemptsImage *attemptsImage = new AttemptsImage(this);
    TimerLabel *timerLabel = new TimerLabel(this);
    bestScoreLabel = new BestScoreLabel(this);
    avatarLabel = new AvatarWidget(currentUser.getAvatarPath(), this);
    LogoutButton *logoutButton = new LogoutButton(this);

    attemptsLabel->setup();
    attemptsImage->setup();
    timerLabel->setup();
    bestScoreLabel->setup();
    avatarLabel->setup();

    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(timerLabel);
    infoLayout->addWidget(avatarLabel);
    infoLayout->addWidget(attemptsImage);
    infoLayout->addWidget(attemptsLabel, 0, Qt::AlignRight);
    infoLayout->addWidget(settingsButton, 0, Qt::AlignRight);
    infoLayout->addWidget(logoutButton, 0, Qt::AlignRight);

    layout->addLayout(infoLayout);
    layout->addWidget(gameButton, 0, Qt::AlignCenter);
    layout->addWidget(bestScoreLabel);

    connect(gameButton, &QPushButton::clicked, this, &MenuWidget::startGame);
    connect(settingsButton, &QPushButton::clicked, this, &MenuWidget::openSettings);
    connect(logoutButton, &QPushButton::clicked, this, &MenuWidget::logout);

    setBackground("back.jpg");
}

void MenuWidget::updateUser(const User &user) {
    currentUser = user;
    avatarLabel->setAvatar(user.getAvatarPath());
    updateAvatar(currentUser.getAvatarPath());
    updateBestScore();
    updateAttempts();
}

void MenuWidget::updateAvatar(const QString &avatarPath) {
    avatarLabel->setAvatar(avatarPath);
}

void MenuWidget::updateBestScore() {
    qDebug() << "Updating best score";
    if (userManager && userManager->getUsers().contains(currentUser.getNickname())) {
        int bestScore = userManager->getUsers().value(currentUser.getNickname()).getBestScore();
        qDebug() << "Current best score:" << bestScore;
        bestScoreLabel->setScore(bestScore);
    } else {
        qDebug() << "User not found or userManager is null";
    }
}

void MenuWidget::updateAttempts() {
    attemptsLabel->setText(QString("%1/5").arg(currentUser.getAttempts()));
}

void MenuWidget::setBackground(const QString& imagePath) {
    BaseWidget::setBackground(imagePath); // Вызов метода базового класса
}

GameWidget::GameWidget(QWidget *parent, UserManager *userManager, const User &currentUser)
    : BaseWidget(parent), userManager(userManager), currentUser(currentUser) {
    backButton = new ReturnButton(this);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    connect(backButton, &QPushButton::clicked, this, &GameWidget::backToMenu);
    connect(backButton, &QPushButton::clicked, this, &GameWidget::resetGame);

    scoreLabel = new QLabel(QString("Score: %1").arg(currentScore), this);
    scoreLabel->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");

    infoLayout->addWidget(backButton);
    infoLayout->addWidget(scoreLabel,0, Qt::AlignRight);
    infoLayout->setAlignment(Qt::AlignTop);

    layout->addLayout(infoLayout);

    gameLogic = new GameLogic(this, 60); // bpm
    connect(gameLogic, &GameLogic::gameEnded, this, &GameWidget::onGameEnded);
}

void GameWidget::setBackground(const QString& imagePath) {
    BaseWidget::setBackground(imagePath); // Вызов метода базового класса
}

void GameWidget::updateUser(const User &user) {
    qDebug() << "iuhygtfrd";
    currentUser = user;
    qDebug() << "Updated user in GameWidget:" << user.getNickname();
    updateBackground(currentUser.getBackgroundPath());
}

void GameWidget::updateBackground(const QString &imagePath) {
    qDebug() << "Updating background to" << imagePath;
    setBackground(imagePath);
}

void GameWidget::startGame() {
    qDebug() << "Starting game!";
    if (currentUser.getAttempts() > 0) {
        currentUser.decreaseAttempt(); // Уменьшаем количество попыток
        userManager->updateAttempts(currentUser.getNickname(), currentUser.getAttempts()); // Сохраняем обновленные данные попыток
        emit attemptsChanged(currentUser.getAttempts()); // Обновляем отображение попыток
        resetGame(); // Сброс состояния игры перед запуском
        gameLogic->startGame();
    } else {
        qDebug() << "No attempts left!";
        // Добавьте логику для обработки ситуации, когда нет попыток
    }
}


void GameWidget::resetGame() {
    qDebug() << "Resetting game!";
    gameLogic->stopGame(); // Останавливаем текущую игру
    gameLogic->removeAllBlocks(); // Удаляем все блоки
    currentScore = 0;
    updateScoreLabel();
}

void GameWidget::onGameEnded() {
    qDebug() << "Game ended!";
    checkAndUpdateBestScore();
    emit gameEnded();
}

void GameWidget::updateScoreLabel() {
    scoreLabel->setText(QString("Score: %1").arg(currentScore));
}

void GameWidget::increaseScore() {
    ++currentScore;
    updateScoreLabel();
}

void GameWidget::checkAndUpdateBestScore() {
    if (!userManager) {
        qDebug() << "UserManager is not initialized!";
        return;

    }
    if (userManager->updateBestScore(currentUser.getNickname(), currentScore)) {
        qDebug() << "Best score updated!";
    } else {
        qDebug() << "Best score not updated!";
    }
}

void GameWidget::setDifficulty(const QString &difficulty) {
    gameLogic->setDifficulty(difficulty);
}

SettingsWidget::SettingsWidget(QWidget *parent) : BaseWidget(parent), currentUsername(""), userManager(nullptr) {

    backButton = new ReturnButton(this);
    layout->addWidget(backButton);

    changeAvatarButton = new ChangeAvatarButton(this);
    changeBackgroundButton = new ChangeBackgroundButton(this);
    changeMusicButton = new ChangeMusicButton(this);
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItems({"Easy", "Medium", "Hard"});

    layout->addWidget(changeAvatarButton);
    layout->addWidget(changeBackgroundButton);
    layout->addWidget(changeMusicButton);
    layout->addWidget(difficultyComboBox);

    connect(backButton, &QPushButton::clicked, this, &SettingsWidget::backToMenu);
    connect(changeAvatarButton, &QPushButton::clicked, this, &SettingsWidget::onChangeAvatarClicked);
    connect(changeBackgroundButton, &QPushButton::clicked, this, &SettingsWidget::onChangeBackgroundClicked);
    connect(changeMusicButton, &QPushButton::clicked, this, &SettingsWidget::onChangeMusicClicked);
    connect(difficultyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsWidget::onDifficultyChanged);
    setBackground("back.jpg");
}

void SettingsWidget::setUserManager(UserManager *userManager) {
    this->userManager = userManager;

    avatarSetting = new AvatarSetting(userManager, this);
    backgroundSetting = new BackgroundSetting(userManager, this);
    musicSetting = new MusicSetting(userManager, this);
    difficultySetting = new DifficultySetting(difficultyComboBox, userManager, this);

    connect(avatarSetting, &Setting::settingChanged, this, [this](const QString &filePath) {
        qDebug() << "Avatar changed to" << filePath;
        emit avatarChanged(filePath);
    });
    connect(backgroundSetting, &Setting::settingChanged, this, [this](const QString &filePath) {
        qDebug() << "Background changed to" << filePath;
        emit backgroundChanged(filePath);
    });
    connect(musicSetting, &Setting::settingChanged, this, [this](const QString &filePath) {
        qDebug() << "Music changed to" << filePath;
        emit musicChanged(filePath);
    });
}

void SettingsWidget::setBackground(const QString& imagePath) {
    BaseWidget::setBackground(imagePath); // Вызов метода базового класса
}

void SettingsWidget::setCurrentUser(const QString &username) {
    currentUsername = username;
}

void SettingsWidget::onChangeAvatarClicked() {
    avatarSetting->applySetting(currentUsername, "");
}

void SettingsWidget::onChangeBackgroundClicked() {
    backgroundSetting->applySetting(currentUsername, "");
}

void SettingsWidget::onChangeMusicClicked() {
    musicSetting->applySetting(currentUsername, "");
}

void SettingsWidget::onDifficultyChanged(int index) {
    difficultySetting->applySetting(currentUsername, difficultyComboBox->itemText(index));
    emit difficultyChanged(difficultyComboBox->itemText(index));
}


GameOverWidget::GameOverWidget(QWidget *parent)
    : BaseWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    QVBoxLayout *layout = new QVBoxLayout(this);
    gameOverLabel = new QLabel(this);
    QPixmap gameover("i_logo.png");
    gameOverLabel->setFixedSize(350, 50);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setPixmap(gameover.scaled(gameOverLabel->size(), Qt::KeepAspectRatioByExpanding));
    gameOverLabel->setStyleSheet("QLabel { background-color: transparent; }");

    playAgainButton = new StartButton (this);
    returnButton = new ReturnButton(this);
    layout->addSpacerItem(new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setFixedSize(350,150);

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addStretch();
    buttonLayout->addWidget(playAgainButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(returnButton);
    buttonLayout->addStretch();
    buttonContainer->setLayout(buttonLayout);

    connect(playAgainButton, &QPushButton::clicked, this, &GameOverWidget::onPlayAgainButtonClicked);
    connect(returnButton, &QPushButton::clicked, this, &GameOverWidget::onReturnButtonClicked);

    layout->addWidget(gameOverLabel);
    layout->addWidget(buttonContainer);

    setLayout(layout);
    setBackground("back.jpg");
}

void GameOverWidget::onPlayAgainButtonClicked() {
    emit playAgain();
}

void GameOverWidget::onReturnButtonClicked() {
    emit returnToMenu();
}

void GameOverWidget::setBackground(const QString& imagePath) {
    BaseWidget::setBackground(imagePath);
}
