#include "game.h"
#include <QGraphicsScene>
#include <button.h>
#include <QBrush>
#include <QImage>
#include <iostream>
#include <QDebug>
#include <QtMath>
using namespace std;


Game::Game(QWidget *parent)
{
    Player_Max_SettedInLine = 0;
    PC_Max_SettedInLine = 0;
    Counter = 0;
   // setBackgroundBrush(QBrush(QImage(":/Pictures/cbg4.png")));

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);

    //set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    //set up the scene
    setScene(scene);
    if (General_X == 3 && General_Y == 3)
        AshNum = 2;

}

void Game::start(int x, int y, int k)
{
    int Box_Width = 800 / x;
    int Box_Heigth = 700 / y;


    scene->clear(); //Clear screen

    bboxboard = new BoxBoard(General_Y, General_X);
    bboxboard->PlaceBoxes(112,32,Box_Width,Box_Heigth,x,y,72);
    bboxboard->PrintTable();
    DrawGUI();

    if (WhosTurn == 0)
     GamePlay();

}

//Displaying the menue that you choose the Greed lengthes in it
void Game::DisplayChoosGreedsMenue()
{
    scene->clear();

    QImage *image = new QImage(":/Pictures/c-bg.png","PNG");
    if(image->isNull()) {
            std::cout << "Failed to load the image." <<std::endl;
        } else {
            QBrush *brush = new QBrush(*image);
            setBackgroundBrush(*brush);
        }

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("choose The Board Width"));
    QFont titleFont("comic sans",20);
    titleText->setFont(titleFont);
    int title_xPos = 100;//this->width()/2 - titleText->boundingRect().width()/2;
    int title_yPos = 150;
    titleText->setPos(title_xPos, title_yPos);
    scene->addItem(titleText);



    WidthShower = new QGraphicsTextItem(QString("3"));
    WidthShower->setFont(titleFont);
    int WidthShower_xPos = 760;//this->width()/2 - WidthShower->boundingRect().width()/2;
    int WidthShower_yPos = 220;
    WidthShower->setPos(WidthShower_xPos, WidthShower_yPos);
    WidthShower->setTextInteractionFlags(Qt::TextEditorInteraction);
    scene->addItem(WidthShower);

    QGraphicsRectItem* border1 = new QGraphicsRectItem();
    border1->setRect(WidthShower_xPos-30,WidthShower_yPos,100,40);
    scene->addItem(border1);

    lengthShower = new QGraphicsTextItem(QString("3"));
    lengthShower->setFont(titleFont);
    int lengthShower_xPos = 450;//this->width()/2 - WidthShower->boundingRect().width()/2;
    int lengthShower_yPos = 470;
    lengthShower->setPos(lengthShower_xPos, lengthShower_yPos);
    scene->addItem(lengthShower);
    \
    QGraphicsRectItem* border2 = new QGraphicsRectItem();
    border2->setRect(lengthShower_xPos-30,lengthShower_yPos,100,40);
    scene->addItem(border2);

    lengthShower->setTextInteractionFlags(Qt::TextEditorInteraction);


    Button* Next_Button = new Button(QString("Next"));
    int NextBut_xPos = 100; //this->width()/2 - Quit_Button->boundingRect().width()/2;
    int NextBut_yPos = 600;
    Next_Button->setPos(NextBut_xPos, NextBut_yPos);
    connect(Next_Button, SIGNAL(clicked()),this,SLOT(SetXYlength()));

    scene->addItem(Next_Button);

}

void Game::DisPlayWinnerLengthMenue()
{
    scene->clear();

    QImage *image = new QImage(":/Pictures/wl-bg.png","PNG");
    if(image->isNull()) {
            std::cout << "Failed to load the image." <<std::endl;
        } else {
            QBrush *brush = new QBrush(*image);
            setBackgroundBrush(*brush);
        }

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Choose the Winnig length"));
    QFont titleFont("comic sans",20);
    titleText->setFont(titleFont);
    int title_xPos = 100;//this->width()/2 - titleText->boundingRect().width()/2;
    int title_yPos = 150;
    titleText->setPos(title_xPos, title_yPos);
    scene->addItem(titleText);

    winningLengthShower = new QGraphicsTextItem(QString("3"));
    winningLengthShower->setFont(titleFont);
    int winningLengthShower_xPos = 760;//this->width()/2 - WidthShower->boundingRect().width()/2;
    int winningLengthShower_yPos = 220;
    winningLengthShower->setPos(winningLengthShower_xPos, winningLengthShower_yPos);
    scene->addItem(winningLengthShower);
    winningLengthShower->setTextInteractionFlags(Qt::TextEditorInteraction);

    QGraphicsRectItem* border1 = new QGraphicsRectItem();
    border1->setRect(winningLengthShower_xPos-30,winningLengthShower_yPos,100,40);
    scene->addItem(border1);


    Button* Next_Button = new Button(QString("Next"));
    int NextBut_xPos = 100; //this->width()/2 - Quit_Button->boundingRect().width()/2;
    int NextBut_yPos = 600;
    Next_Button->setPos(NextBut_xPos, NextBut_yPos);
    connect(Next_Button, SIGNAL(clicked()),this,SLOT(SetKlength()));
    scene->addItem(Next_Button);

}

void Game::DisplayTurnChooserMenue()
{
    scene->clear();

    setBackgroundBrush(QBrush(Qt::white));

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Who Starts?  Me OR You?"));
    QFont titleFont("comic sans",20);
    titleText->setFont(titleFont);
    int title_xPos = 100;//this->width()/2 - titleText->boundingRect().width()/2;
    int title_yPos = 150;
    titleText->setPos(title_xPos, title_yPos);
    scene->addItem(titleText);

    Button* PC_Starter_Button = new Button(QString("PC"));
    int PC_Starter_Button_xPos = 300; //this->width()/2 - Quit_Button->boundingRect().width()/2;
    int PC_Starter_Button_yPos = 400;
    PC_Starter_Button->setPos(PC_Starter_Button_xPos, PC_Starter_Button_yPos);
    connect(PC_Starter_Button, SIGNAL(clicked()),this,SLOT(SetFirstPlayer_PC()));
    scene->addItem(PC_Starter_Button);

    Button* PLayer_Starter_Button = new Button(QString("YOU"));
    int PLayer_Starter_Button_xPos = 510; //this->width()/2 - Quit_Button->boundingRect().width()/2;
    int PLayer_Starter_Button_yPos = 400;
    PLayer_Starter_Button->setPos(PLayer_Starter_Button_xPos, PLayer_Starter_Button_yPos);
    connect(PLayer_Starter_Button, SIGNAL(clicked()),this,SLOT(SetFirstPlayer_Player()));
    scene->addItem(PLayer_Starter_Button);
}

void Game::DisplayGameOver(QString mess)
{
    //Disable everything in scene
    int n = scene->items().size();
    for(size_t i = 0; i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    //pop up semi
    DrawPanel(0,0,1024,768, Qt::black, 0.65);

    //draw oanel
    DrawPanel(312,184,400,400,Qt::lightGray,0.75);

    //creat quit button
    Button* Quit = new Button(QString("Quit"));
    Quit->setPos(410,375);
    scene->addItem(Quit);
    connect(Quit,SIGNAL(clicked()),this,SLOT(close()));

    QGraphicsTextItem* Winnertext = new QGraphicsTextItem(mess);
    Winnertext->setPos(460,225);
    QFont titleFont("comic sans",20);
    Winnertext->setFont(titleFont);
    scene->addItem(Winnertext);
}

void Game::SetXYlength()
{

    General_X = WidthShower->document()->toPlainText().toInt();
    General_Y = lengthShower->document()->toPlainText().toInt();

    if (General_X == 3 && General_Y == 3)
        AshNum = 2;

    if ((General_X >= 3 && General_Y >= 3) && (General_X <100 && General_Y < 100) )
        DisPlayWinnerLengthMenue();

}

void Game::SetKlength()
{
    General_K = winningLengthShower->document()->toPlainText().toInt();
//    bboxboard->Winner_Length = General_K;
    if (General_K >= 3 && General_K <= General_Y && General_K <= General_X)
        DisplayTurnChooserMenue();

}

void Game::SetFirstPlayer_PC()
{
    WhosTurn = 0;
    starter = 0;
    start(General_X, General_Y, General_K);
}

void Game::SetFirstPlayer_Player()
{
    WhosTurn = 1;
    starter = 1;
    start(General_X, General_Y, General_K);

}

void Game::DisplayMainMenue()
{
    //create thew title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Tic Tac Toe"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int title_xPos = this->width()/2 - titleText->boundingRect().width()/2;
    int title_yPos = 150;
    titleText->setPos(title_xPos, title_yPos);
    scene->addItem(titleText);

    //creat Play button
    Button* Play_Button = new Button(QString("Play"));
    int Playbut_xPos = this->width()/2 - Play_Button->boundingRect().width()/2;
    int playbut_yPos = 375;
    Play_Button->setPos(Playbut_xPos, playbut_yPos);
    connect(Play_Button,SIGNAL(clicked()),this,SLOT(DisplayChoosGreedsMenue()));
    scene->addItem(Play_Button);

    //creat Quit Button

    Button* Quit_Button = new Button(QString("Quit"));
    int QuitBut_xPos = this->width()/2 - Play_Button->boundingRect().width()/2;
    int QuitBut_yPos = 450;
    Quit_Button->setPos(QuitBut_xPos, QuitBut_yPos);
    connect(Quit_Button, SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(Quit_Button);

}

QString Game::getWhosTurn()
{
    if(WhosTurn == 1)
        return QString("YOU");
    else
        return QString("PC");
}

void Game::setWhosTurn(int a)
{
    WhosTurn = a;
    if (a == 1)
        WhosTurntext->setPlainText(QString("YOUR TURN"));
    else
        WhosTurntext->setPlainText(QString("MY TURN"));

}

void Game::DrawPanel(int x, int y, int w, int h, QColor color, double opacity)
{
    //draw panel at specified location with specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,w,h);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::DrawGUI()
{
    //draw panels

    DrawPanel(0,0,62,768,Qt::darkCyan,1);
    DrawPanel(974,0,62,768,Qt::darkCyan,1);

    //place WhosTurn Text
    WhosTurntext = new QGraphicsTextItem();
    setWhosTurn(WhosTurn);
    QFont font("comic sans", 14);
    WhosTurntext->setPos(490,0);
    WhosTurntext->setFont(font);
    scene->addItem(WhosTurntext);
}

void Game::GamePlay()
{
 //   while(GameIsOn){
        if(Counter == 0 && WhosTurn == 0){
            bboxboard->PC_TapIn(General_X/2, General_Y/2);
        //    Counter++;
            setWhosTurn(1);
        }

        else if(WhosTurn == 0){

           AlphaCordinates TappingCords;
           QList<QList<SquareBox*>> SecondSaverTable;
           SecondSaverTable = bboxboard->SquareSaverTable;

           QList<QList<short int>> PropertyMap;          //making a table of short ints to
           for (int i = 0 ; i < General_Y; i++){    //pass to AlphaBeta and doing the calculations
               QList<short int> listak;
               PropertyMap.push_back(listak);
           }
           for (int i = 0 ; i < General_Y; i++){
               for(int j = 0; j < General_X;j++)
                   PropertyMap[i].push_back(bboxboard->SquareSaverTable[i].at(j)->Owner);
         }

           for (int z = 0; z < General_Y; z++)
                       qDebug() << PropertyMap[z].at(0)<< QString( )<< PropertyMap[z].at(1) << QString( )
                                   << PropertyMap[z].at(2);/* << QString( )<< PropertyMap[z].at(3) << QString( )
                                   << PropertyMap[z].at(4) << QString( )<< PropertyMap[z].at(5) << QString( )
                                   << PropertyMap[z].at(6);*/
            qDebug() << QString("------------------------");

           TappingCords = AlphaBeta(PropertyMap,AshNum, -9998 , 9999, 1, Counter,bboxboard->Max_Left_Check,bboxboard->Max_Up_Check);
           if (Counter == (General_X * General_Y) / 2 + 1 && starter == 1 && TappingCords.X == 0 && TappingCords.Y ==0){
               DisplayGameOver("Tie Game");
               return;
           }
           bboxboard->PC_TapIn(TappingCords.X, TappingCords.Y);
    //       Counter++;
           setWhosTurn(1);

        }



 //   }
}

AlphaCordinates Game::AlphaBeta(QList<QList<short int>> OwnersMap,int TreeDepth, int Alpha, int Beta, bool Maximizing_Palyer, int DepthCounter, int SquareX, int SquareY)
{


    for(int z = 0; z < General_Y; z++){
//        for (int y = 0; y < General_X; y++)
            qDebug() << OwnersMap[z].at(0) << QString( )<< OwnersMap[z].at(1) << QString( )
                        << OwnersMap[z].at(2);/* << QString( )<< NewTable[z].at(3)->Owner << QString( )
                        << NewTable[z].at(4)->Owner << QString( )<< NewTable[z].at(5)->Owner << QString( )
                        << NewTable[z].at(6)->Owner;*/
    }
    qDebug() << QString("------------------------");


    QList<QList<short int>> NewTable;
    NewTable = OwnersMap;
    int CheckingForFinalRate = StateRating(NewTable, SquareX, SquareY, Maximizing_Palyer);

    AlphaCordinates NewCors;
    if (Player_Max_SettedInLine == General_K - 1 || PC_Max_SettedInLine == General_K - 1 || /*DepthCounter - 1  == (General_X * General_Y) / 2 ||*/
        TreeDepth == 0 || CheckingForFinalRate == 100 || CheckingForFinalRate == -99 && TreeDepth != AshNum){
        if (TreeDepth == AshNum){
            qDebug() << QString("Player  Wone The Game");
            //return;
        }
        AlphaCordinates NewCors;
        NewCors.X = SquareX;
        NewCors.Y = SquareY;
       // int temp = StateRating(NewTable, SquareX, SquareY, Maximizing_Palyer);
        NewCors.Value = CheckingForFinalRate;
        return NewCors;
    }

   else if (Maximizing_Palyer)
    {
        for (int j = bboxboard->Max_Up_Check; j < bboxboard->Max_Down_Check; j++){
           for (int i = bboxboard->Max_Left_Check; i < bboxboard->Max_Right_Check; i++){
               if (OwnersMap[j].at(i) != 0 && OwnersMap[j].at(i) != 1){
                       QList<QList<short int>> NewTable;
                       NewTable = OwnersMap;


                       for(int z = 0; z < General_Y; z++){
                   //        for (int y = 0; y < General_X; y++)
                               qDebug() << NewTable[z].at(0) << QString( )<< NewTable[z].at(1) << QString( )
                                           << NewTable[z].at(2); /*<< QString( )<< NewTable[z].at(3) << QString( )
                                           << NewTable[z].at(4) << QString( )<< NewTable[z].at(5) << QString( )
                                           << NewTable[z].at(6);*/
                       }
                       qDebug() << QString("------------------------");


                       NewTable[j].replace(i, 0);
                       AlphaCordinates NewCors3 = AlphaBeta(NewTable, TreeDepth-1, Alpha, Beta, false, DepthCounter+1, i, j);
                       if (Alpha < NewCors3.Value){
                             NewCors.X = i;
                             NewCors.Y = j;
                       }
                       Alpha = max (Alpha, NewCors3.Value);
                       if (Alpha >= fabs(Beta)){
                            break;
                       }
                }
            }
            if (Alpha >= fabs(Beta))
                  break;
        }
        NewCors.Value = Alpha;
        return NewCors;
    }
    else if(Maximizing_Palyer == false)
    {
        for (int j = bboxboard->Max_Up_Check; j < bboxboard->Max_Down_Check; j++){
           for (int i = bboxboard->Max_Left_Check; i < bboxboard->Max_Right_Check; i++){
               if (OwnersMap[j].at(i) != 0 && OwnersMap[j].at(i) != 1){



                   qDebug() << QString("------------------------");
                   QList<QList<short int>> NewTable;
                   NewTable = OwnersMap;

                   NewTable[j].replace(i, 1);
                   AlphaCordinates NewCors2 = AlphaBeta(NewTable, TreeDepth-1, Alpha, Beta, true, DepthCounter, i, j);
                   if (Beta > NewCors2.Value){
                     NewCors.X = i;
                     NewCors.Y = j;
                   }
                   Beta = min (Beta, NewCors2.Value);
                   if (Alpha >= fabs(Beta))
                        break;

             }
          }
           if (Alpha >= fabs(Beta))
                break;
       }
        NewCors.Value = Beta;
        return NewCors;
    }
}


int Game::StateRating(QList<QList<short int>> OwnersMap, int x, int y, int Player)
{
//    QList<QList<short int>> NewTable;
 //   NewTable = OwnersMap;
    int Count_R, Count_L, Count_U, Count_D, Count_RU, Count_RD, Count_LU, Count_LD;
        Count_R = Count_L = Count_U = Count_D = Count_RU = Count_RD = Count_LU = Count_LD = 0;
    for(int z = 0; z < General_Y; z++){
//        for (int y = 0; y < General_X; y++)
            qDebug() << OwnersMap[z].at(0) << QString( )<< OwnersMap[z].at(1) << QString( )
                        << OwnersMap[z].at(2);/* << QString( )<< OwnersMap[z].at(3) << QString( )
                        << OwnersMap[z].at(4) << QString( )<< OwnersMap[z].at(5) << QString( )
                        << OwnersMap[z].at(6);*/
    }
    int Bat_R = bboxboard->Max_Right_Check;
    int Bat_L = bboxboard->Max_Left_Check;
    int Bat_D = bboxboard->Max_Down_Check;
    int Bat_U = bboxboard->Max_Up_Check;


    for(int i = 1; i < Bat_R - x; i++){
        if (OwnersMap[y].at(x+i) == Player)
            Count_R++;
        else
            break;
    }
    for(int i = 1; i <= x - Bat_L; i++){
        if (OwnersMap[y].at(x-i) == Player){
            int KOS = OwnersMap[y].at(x-i);
            Count_L++;
        }
        else
            break;
    }
    for(int i = 1; i < Bat_D - y; i++){
        if (OwnersMap[y+i].at(x) == Player)
            Count_D++;
        else
            break;
    }
    for(int i = 1; i <= y - Bat_U; i++){
        if (OwnersMap[y-i].at(x) == Player)
            Count_U++;
        else
            break;
    }
    int i = 1;
    while (x + i < Bat_R && y + i < Bat_D){       //counting Buttom right line
        if (OwnersMap[y+i].at(x+i) == Player){
            Count_RD++;
            i++;
        }
        else
            break;
    }
    i = 1;
    while (x + i < Bat_R && y - i >= Bat_U){       //counting Right Up line
        if (OwnersMap[y-i].at(x+i) == Player){
            Count_RU++;
            i++;
        }
        else
            break;
    }
    i = 1;
    while (x - i >= Bat_L && y - i >= Bat_U){       //counting left Up line
        if (OwnersMap[y-i].at(x-i) == Player){
            Count_LU++;
            i++;
        }
        else
            break;
    }
    i = 1;
    while (x - i >= Bat_L && y + i < Bat_D){       //counting left down line
        if (OwnersMap[y+i].at(x-i) == Player){
            Count_LD++;
            i++;
        }
        else
            break;
    }

    int VerticalCount = Count_U + Count_D + 1;
    int HorizantalCount = Count_L + Count_R + 1;
    int UpRightCount = Count_RU + Count_LD + 1;
    int UpLeftCount = Count_LU + Count_RD + 1;

    int result = 0; // max(VerticalCount, HorizantalCount, UpRightCount, UpLeftCount)

    if (VerticalCount >result)
        result = VerticalCount;
    if (HorizantalCount > result)
        result = HorizantalCount;
    if (UpRightCount > result)
        result = UpRightCount;
    if (UpLeftCount > result)
        result = UpLeftCount;

    if (result == General_K){
       /* if(Player == 1){
            if (Player_Max_SettedInLine < result)
             Player_Max_SettedInLine = result;
        }
        else if (Player == 0){
            if (PC_Max_SettedInLine < result)
            PC_Max_SettedInLine = result;
                }*/
        if(Player == 0)
            return 100;
        else if (Player == 1)
            return -99;
    }
    else{
        double test = double(result) / General_K;
        test *= 100;
        if (Player == 1)
            test *= -1;
        return test;
    }
}




