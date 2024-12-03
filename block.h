#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>

class Block : public QWidget {
    Q_OBJECT

public:
    explicit Block(int column, QWidget *parent = nullptr);

    int getColumn() const;
    void moveUp(int speed);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked(Block *block);

private:
    int column;
    int position;
};

#endif // BLOCK_H
