#ifndef SQUAREBOX_H
#define SQUAREBOX_H
#include <QGraphicsRectItem>


class SquareBox:public QGraphicsRectItem{
public:
    SquareBox(int W, int H,int In_Board_X,int In_Board_Y, QGraphicsItem* parent=NULL);

    int X;
    int Y;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void SetOwner(bool O);
    int GetOwner();
    void ChangeColorToBlue();
    int Owner;

};

#endif // SQUAREBOX_H
