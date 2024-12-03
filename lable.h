#ifndef LABLE_H
#define LABLE_H

#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>

class CustomLabel : public QLabel {
    Q_OBJECT

public:
    explicit CustomLabel(QWidget *parent = nullptr);
    virtual ~CustomLabel() = default;
    virtual void setup() = 0;
protected:
    void setProperties(int width, int height);
};

class AttemptsLabel : public CustomLabel {
    Q_OBJECT

public:
    explicit AttemptsLabel(QWidget *parent = nullptr);
    void setup() override;
};

// Класс AttemptsImage
class AttemptsImage : public CustomLabel {
    Q_OBJECT

public:
    explicit AttemptsImage(QWidget *parent = nullptr);
    void setup() override;

private:
    QPixmap attemptsPixmap;
};

// Класс TimerLabel
class TimerLabel : public CustomLabel {
    Q_OBJECT

public:
    explicit TimerLabel(QWidget *parent = nullptr);
    void setup() override;
};

// Класс BestScoreLabel

class BestScoreLabel : public CustomLabel {
    Q_OBJECT

public:
    explicit BestScoreLabel(QWidget *parent = nullptr);
    void setup();
    void setScore(int score); // Метод для установки текста счета
};

class AvatarWidget : public CustomLabel {
    Q_OBJECT

public:
    explicit AvatarWidget(const QString &avatarPath, QWidget *parent = nullptr);
    void setup() override;
    void setAvatar(const QString &avatarPath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString avatarPath;
    QPixmap avatarPixmap;
};

#endif // LABLE_H
