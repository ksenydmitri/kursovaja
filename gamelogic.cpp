#include "gamelogic.h"
#include "basewidget.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>

GameLogic::GameLogic(GameWidget *gameWidget, int bpm, QObject *parent)
    : QObject(parent), gameWidget(gameWidget), bpm(bpm), speedMultiplier(1.0) {
    spawnTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    difficultyTimer = new QTimer(this);

    connect(spawnTimer, &QTimer::timeout, this, &GameLogic::spawnBlock);
    connect(moveTimer, &QTimer::timeout, this, &GameLogic::moveBlocks);
    connect(difficultyTimer, &QTimer::timeout, this, &GameLogic::increaseSpeed);

    srand(static_cast<unsigned>(time(nullptr)));  // Инициализация генератора случайных чисел
}

void GameLogic::startGame() {
    qDebug() << "Starting game with BPM:" << bpm;
    spawnTimer->start(30000 / bpm); // Время появления нового блока
    moveTimer->start(1000 / 60);    // Частота обновления движения блоков (60 FPS)
    difficultyTimer->start(15000);  // Увеличение сложности каждые 15 секунд
}

void GameLogic::stopGame() {
    qDebug() << "Stopping game.";
    spawnTimer->stop();
    moveTimer->stop();
    difficultyTimer->stop();
    speedMultiplier = 1.0; // Сброс множителя скорости
}

QList<Block*> GameLogic::getBlocks() const {
    return blocks;
}

void GameLogic::removeAllBlocks() {
    qDebug() << "Removing all blocks.";
    while (!blocks.isEmpty()) {
        removeBlock(blocks.first());
    }
}

void GameLogic::spawnBlock() {
    qDebug() << "Spawning block. Current block count:" << blocks.size();
    if (blocks.size() < 4) {
        int column = rand() % 4;
        Block *block = new Block(column, gameWidget);
        connect(block, &Block::clicked, this, &GameLogic::removeBlock);
        blocks.append(block);
        block->show();
    }
}

void GameLogic::moveBlocks() {
    qDebug() << "Moving blocks. Current block count:" << blocks.size();
    double speed = gameWidget->height() / (2*3600 / bpm);  // Скорректированный расчет скорости движения блоков
    speed *= speedMultiplier; // Учитываем множитель скорости
    for (Block *block : qAsConst(blocks)) {
        block->moveUp(speed);

        // Проверка на достижение верхней границы
        if (block->y() < 0) {
            stopGame();
            emit gameEnded();
            return;
        }
    }
}

void GameLogic::removeBlock(Block *block) {
    if (block) {
        qDebug() << "Removing block.";
        blocks.removeOne(block);
        block->deleteLater();
        gameWidget->increaseScore();
    }
}

void GameLogic::setDifficulty(const QString &difficulty) {
    if (difficulty == "Easy") {
        bpm = 30;
    } else if (difficulty == "Medium") {
        bpm = 60;
    } else if (difficulty == "Hard") {
        bpm = 120;
    }
    qDebug() << "Difficulty set to:" << difficulty << "with BPM:" << bpm;
}

void GameLogic::increaseSpeed() {
    speedMultiplier *= 1.2;  // Увеличиваем множитель скорости на 20%
    double newSpawnInterval = static_cast<int>((15000 / bpm) / speedMultiplier);
    qDebug() << "Increasing speed. New spawn interval:" << newSpawnInterval << "ms, speed multiplier:" << speedMultiplier;

    // Обновляем частоту спавна блоков
    spawnTimer->start(newSpawnInterval);

    // Обновляем скорость уже заспавненных блоков
    for (Block *block : qAsConst(blocks)) {
        block->moveUp(0);  // Обновляем позиции блоков с новым множителем скорости
    }
}
