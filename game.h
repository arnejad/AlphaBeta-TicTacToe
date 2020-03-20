#ifndef GAME_H
#define GAME_H

#include "boxboard.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTextDocument>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

struct AlphaCordinates{
    int Value = 0;
    int X = 0;
    int Y = 0;
};

class Game : public QGraphicsView{
    Q_OBJECT
public:
    //constructor
    Game(QWidget* parent=NULL);

    //public methods
    void DisplayMainMenue();

    //public attributes
    QGraphicsScene* scene;
    BoxBoard* bboxboard;
    int General_X;
    int General_Y;
    int General_K;
    bool WhosTurn;
    int AshNum = 4;
    QString getWhosTurn();
    void setWhosTurn(int a);
    int Counter;        //For counting the the number of the moves done in the game
    bool starter;

    int PC_Max_SettedInLine;        //Keeps the longest line that PC had made
    int Player_Max_SettedInLine;    //Keeps ''  ''          ''  player '' ''
    void GamePlay();

private:

    QGraphicsTextItem* WidthShower;
    QGraphicsTextItem* lengthShower;
    QGraphicsTextItem* winningLengthShower;
    void DrawPanel(int x, int y, int w, int h, QColor color, double opacity);
    void DrawGUI();
    QGraphicsTextItem* WhosTurntext;
    AlphaCordinates AlphaBeta(QList<QList<short int>> OwnersMap,int TreeDepth, int Alpha, int Beta, bool Maximizing_Palyer, int DepthCounter, int SquareX, int SquareY);
    int StateRating(QList<QList<short int>> OwnersMap,int x, int y,int Player);



public slots:
    void start(int x, int y, int k);
    void DisplayChoosGreedsMenue();
    void DisPlayWinnerLengthMenue();
    void DisplayTurnChooserMenue();
    void DisplayGameOver(QString mess);
    void SetXYlength();
    void SetKlength();
    void SetFirstPlayer_PC();
    void SetFirstPlayer_Player();

};

#endif // GAME_H
