#include "boxboard.h"
#include "game.h"

#include <iostream>
using namespace std;

extern Game* mainGame;


BoxBoard::BoxBoard(int m, int n)
{
    for(int i = 0; i<m;i++){
        QList<SquareBox*> NewVec;
        SquareSaverTable.push_back(NewVec);
    }
    Max_Down_Check = mainGame->General_Y / 2 + mainGame->General_K / 2;
    Max_Up_Check = mainGame->General_Y / 2 - mainGame->General_K / 2;
    Max_Left_Check = mainGame->General_K - mainGame->General_K / 2;
    Max_Right_Check = mainGame->General_X / 2 + mainGame->General_K / 2;
}

void BoxBoard::PlaceBoxes(int x, int y,int Box_W, int Box_H, int NumOfRows,int NumOfCols,int Shift)
{
    for(int j = 0; j< NumOfCols; j++){
        for(int i = 0; i< NumOfRows; i++){
            SquareBox* box = new SquareBox(Box_W,Box_H,i,j);
            box->setPos(x+(Box_W*i),y+(Box_H*j));
            Add_Sq_Table(box, i,j);
            mainGame->scene->addItem(box);
        }
    }
}

//adding each new square in our SquareSaverTable which is a 2D QVector
void BoxBoard::Add_Sq_Table(SquareBox * &NewBox, int x, int y)
{
    SquareSaverTable[y].push_back(NewBox);
}

void BoxBoard::PrintTable() //test
{
    for (int i =0; i < SquareSaverTable[1].size();i++){
    cout << SquareSaverTable[1].at(i)->X<<"  ";
    }
    cout<<"  ";
//    int testOwner = SquareSaverTable[0].at(6)->GetOwner();
  //  cout << testOwner;
}

//coloring a specified Box in the board with Specified Cordinates
void BoxBoard::PC_TapIn(int x, int y)
{
    SquareSaverTable[y].at(x)->SetOwner(0);
    SquareSaverTable[y].at(x)->ChangeColorToBlue();

    int Count_R, Count_L, Count_U, Count_D, Count_RU, Count_RD, Count_LU, Count_LD;
        Count_R = Count_L = Count_U = Count_D = Count_RU = Count_RD = Count_LU = Count_LD = 0;

    int Bat_R = Max_Right_Check;
    int Bat_L = Max_Left_Check;
    int Bat_D = Max_Down_Check;
    int Bat_U = Max_Up_Check;


    for(int i = 1; i < Bat_R - x; i++){
        if (SquareSaverTable[y].at(x+i)->Owner == 0)
            Count_R++;
        else
            break;
    }
    for(int i = 1; i <= x - Bat_L; i++){
        if (SquareSaverTable[y].at(x-i)->Owner == 0){
            Count_L++;
        }
        else
            break;
    }
    for(int i = 1; i < Bat_D - y; i++){
        if (SquareSaverTable[y+i].at(x)->Owner == 0)
            Count_D++;
        else
            break;
    }
    for(int i = 1; i <= y - Bat_U; i++){
        if (SquareSaverTable[y-i].at(x)->Owner == 0)
            Count_U++;
        else
            break;
    }
    int i = 1;
    while (x + i < Bat_R && y + i < Bat_D){       //counting Buttom right line
        if (SquareSaverTable[y+i].at(x+i)->Owner == 0){
            Count_RD++;
            i++;
        }
        else
            break;
    }
    i = 1;
    while (x + i < Bat_R && y - i >= Bat_U){       //counting Right Up line
        if (SquareSaverTable[y-i].at(x+i)->Owner == 0){
            Count_RU++;
            i++;
        }
        else
            break;
    }
    i = 1;
    while (x - i >= Bat_L && y - i >= Bat_U){       //counting left Up line
        if (SquareSaverTable[y-i].at(x-i)->Owner == 0){
            Count_LU++;
            i++;
        }
        else
            break;
    }
    i = 1;
    while (x - i >= Bat_L && y + i < Bat_D){       //counting left down line
        if (SquareSaverTable[y+i].at(x-i)->Owner == 0){
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

    if (result == mainGame->General_K){
        mainGame->DisplayGameOver("You Lost");
    }

    else if (mainGame->Counter == (mainGame->General_Y * mainGame->General_X) / 2 && mainGame->starter == 0)
        mainGame->DisplayGameOver("Tie Game");
}

void BoxBoard::Player_TapIn(int x, int y)
{
        SquareSaverTable[y].at(x)->SetOwner(1);

        Winner_Length = mainGame->General_K;


        // setting dimensions of The BattleField
        if ((x + Winner_Length) > Max_Right_Check && (x + Winner_Length) < mainGame->General_X)
            Max_Right_Check = x + Winner_Length;
        else if ((x + Winner_Length) > Max_Right_Check && (x + Winner_Length) >= mainGame->General_X)
            Max_Right_Check = mainGame->General_X;

        if ((x - Winner_Length) < Max_Left_Check && (x - Winner_Length) > 0)
            Max_Left_Check = x - Winner_Length;
        else if ((x - Winner_Length) < Max_Left_Check && (x - Winner_Length) < 0)
            Max_Left_Check = 0;

        if ((y +  Winner_Length) > Max_Down_Check && (y + Winner_Length) < mainGame->General_Y)
            Max_Down_Check = y + Winner_Length;
        else if ((y +  Winner_Length) > Max_Down_Check && (y +  Winner_Length) >= mainGame->General_Y)
            Max_Down_Check = mainGame->General_Y;

        if ((y - Winner_Length) < Max_Up_Check && (y - Winner_Length) > 0)
            Max_Up_Check = y - Winner_Length;
        else if ((y - Winner_Length) < Max_Up_Check && (y - Winner_Length) < 0)
            Max_Up_Check = 0;



        int Count_R, Count_L, Count_U, Count_D, Count_RU, Count_RD, Count_LU, Count_LD;
            Count_R = Count_L = Count_U = Count_D = Count_RU = Count_RD = Count_LU = Count_LD = 0;

        int Bat_R = Max_Right_Check;
        int Bat_L = Max_Left_Check;
        int Bat_D = Max_Down_Check;
        int Bat_U = Max_Up_Check;


        for(int i = 1; i < Bat_R - x; i++){
            if (SquareSaverTable[y].at(x+i)->Owner == 1)
                Count_R++;
            else
                break;
        }
        for(int i = 1; i <= x - Bat_L; i++){
            if (SquareSaverTable[y].at(x-i)->Owner == 1){
                Count_L++;
            }
            else
                break;
        }
        for(int i = 1; i < Bat_D - y; i++){
            if (SquareSaverTable[y+i].at(x)->Owner == 1)
                Count_D++;
            else
                break;
        }
        for(int i = 1; i <= y - Bat_U; i++){
            if (SquareSaverTable[y-i].at(x)->Owner == 1)
                Count_U++;
            else
                break;
        }
        int i = 1;
        while (x + i < Bat_R && y + i < Bat_D){       //counting Buttom right line
            if (SquareSaverTable[y+i].at(x+i)->Owner == 1){
                Count_RD++;
                i++;
            }
            else
                break;
        }
        i = 1;
        while (x + i < Bat_R && y - i >= Bat_U){       //counting Right Up line
            if (SquareSaverTable[y-i].at(x+i)->Owner == 1){
                Count_RU++;
                i++;
            }
            else
                break;
        }
        i = 1;
        while (x - i >= Bat_L && y - i >= Bat_U){       //counting left Up line
            if (SquareSaverTable[y-i].at(x-i)->Owner == 1){
                Count_LU++;
                i++;
            }
            else
                break;
        }
        i = 1;
        while (x - i >= Bat_L && y + i < Bat_D){       //counting left down line
            if (SquareSaverTable[y+i].at(x-i)->Owner == 1){
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

        if (result == mainGame->General_K)
            mainGame->DisplayGameOver("You Won");


}
