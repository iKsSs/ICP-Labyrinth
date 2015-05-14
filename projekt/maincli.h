//ICP-Labyrinth 2014/2015
/**
 * @file       maincli.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Function headers and class for demonstrate application in CLI.
 */

#ifndef MAINCLI
#define MAINCLI

#include "board.h"
#include <QString>
#include <QPoint>
#include <QTextStream>

/*! Class representing Main CLI window */

class MainCLI{
    Board *board;

public:
    MainCLI();
    ~MainCLI();

    void help();
    QString getTileImage(Tile*);
    QString getPlayerImage(int);
    void genBoard();
    void game();

    bool shift(unsigned int, unsigned int);
    void u_getShift();
    bool move(unsigned int, unsigned int);
    void u_getMove();
};

#endif // MAINCLI

