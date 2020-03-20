#ifndef BOXBOARD_H
#define BOXBOARD_H
#include <QList>
#include "squarebox.h"

class BoxBoard{
public:
    BoxBoard(int m, int n);
    void PlaceBoxes(int x, int y,int Box_W, int Box_H, int NumOfRows,int NumOfCols,int Shift);
    void Add_Sq_Table(SquareBox* &NewBox, int x, int y);
    void PrintTable();  //testing table
    void PC_TapIn(int x, int y);
    void Player_TapIn(int x, int y);
    int Winner_Length = 0;
    int Max_Up_Check;
    int Max_Down_Check;
    int Max_Left_Check;
    int Max_Right_Check;
    QList<QList<SquareBox*>> SquareSaverTable;



};

#endif // BOXBOARD_H
