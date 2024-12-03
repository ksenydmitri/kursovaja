#include "lable.h"

CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent) {}

void CustomLabel::setProperties(int width, int height) {
    this->setFixedSize(width, height);
}

AttemptsLabel::AttemptsLabel(QWidget *parent) : CustomLabel(parent) {}

void AttemptsLabel::setup() {
    setProperties(30, 30);
}

AttemptsImage::AttemptsImage(QWidget *parent) : CustomLabel(parent), attemptsPixmap("attempts.png") {}

void AttemptsImage::setup() {
    setProperties(30, 30);
    this->setPixmap(attemptsPixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    this->setStyleSheet("QLabel { background-color: transparent; }");
}

TimerLabel::TimerLabel(QWidget *parent) : CustomLabel(parent) {}

void TimerLabel::setup() {
    setProperties(100, 30);
}

BestScoreLabel::BestScoreLabel(QWidget *parent) : CustomLabel(parent) {}

void BestScoreLabel::setup() {
    setProperties(200, 30);
    this->setObjectName("bestScoreLabel");
    this->setStyleSheet("color: #FFFFFF; font-size: 16px; background: none;");
}

void BestScoreLabel::setScore(int score) {
    setText("Лучший счет: " + QString::number(score));
}

AvatarWidget::AvatarWidget(const QString &avatarPath, QWidget *parent)
    : CustomLabel(parent), avatarPath(avatarPath) {
    setAvatar(avatarPath);
    setup(); // Вызов метода setup для инициализации параметров
}

void AvatarWidget::setup() {
    setProperties(50, 50);
    setObjectName("avatarImage");
}

void AvatarWidget::setAvatar(const QString &avatarPath) {
    avatarPixmap.load(avatarPath);
    update();
}

void AvatarWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addEllipse(0, 0, width(), height());

    painter.setClipPath(path);
    painter.drawPixmap(0, 0, avatarPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding));
}
