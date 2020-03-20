#include "squarebox.h"
#include <QBrush>
#include "boxboard.h"
#include "game.h"
extern Game* mainGame;

SquareBox::SquareBox(int W, int H, int In_Board_X,int In_Board_Y,QGraphicsItem *parent)
{
    setRect(0,0,W,H);
    X = In_Board_X;
    Y = In_Board_Y;
    Owner = 999;
    setAcceptHoverEvents(true);
}

void SquareBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    emit clicked();
    if (this->Owner != 0 && this->Owner != 1 && mainGame->WhosTurn == 1){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
        mainGame->setWhosTurn(0);
        mainGame->bboxboard->Player_TapIn(this->X, this->Y);
        mainGame->setWhosTurn(0);
        mainGame->Counter++;
        mainGame->GamePlay();


    }

}

void SquareBox::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->brush().color() != Qt::red && this->brush().color() != Qt::blue){

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }
}

void SquareBox::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(this->brush().color() == Qt::lightGray){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        setBrush(brush);
    }
}

void SquareBox::SetOwner(bool O)
{
    Owner = O;
}

int SquareBox::GetOwner()
{
    return Owner;
}


void SquareBox::ChangeColorToBlue()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
//    mainGame->Counter++;
}
