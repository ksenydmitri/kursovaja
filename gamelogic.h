#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "block.h"

class GameWidget;

class GameLogic : public QObject {
    Q_OBJECT

public:
    explicit GameLogic(GameWidget *gameWidget, int bpm, QObject *parent = nullptr);

    void setDifficulty(const QString &difficulty);
    void startGame();
    void stopGame();
    QList<Block*> getBlocks() const;
    void removeAllBlocks();
    void removeBlock(Block *block);

signals:
    void gameEnded();

private slots:
    void spawnBlock();
    void moveBlocks();
    void increaseSpeed();

private:
    GameWidget *gameWidget;
    double bpm;
    double speedMultiplier;
    QList<Block*> blocks;
    QTimer *spawnTimer;
    QTimer *moveTimer;
    QTimer *difficultyTimer;
};

#endif // GAMELOGIC_H
