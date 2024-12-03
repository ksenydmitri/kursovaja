#include "block.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Block::Block(int column, QWidget *parent)
    : QWidget(parent), column(column), position(parent->height()) {
    setFixedSize(parent->width() / 4, parent->height() / 3.9);
    move(column * width(), position);
}

int Block::getColumn() const {
    return column;
}

void Block::moveUp(int speed) {
    position -= speed;
    move(column * width(), position);
    //qDebug() << "Block moved up to position:" << position;

    if (position < 0) {
        emit clicked(nullptr);
    }
}

void Block::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.drawRect(0, 0, width(), height());
}

void Block::mousePressEvent(QMouseEvent *event) {
    emit clicked(this);
}
