#include <QApplication>
#include "game.h"

Game* mainGame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainGame = new Game();
    mainGame->show();
    mainGame->DisplayMainMenue();
    return a.exec();
}

