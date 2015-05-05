#include "player.h"
#include "tile.h"
#include <QPoint>
#include <QVector>
#include <qglobal.h>

#ifndef BOARD
#define BOARD

class Board
{
    QVector<TileCorner> tiles;
    QVector<Player> players;
    Tile newTile;

    //...
    QVector<Board> board;
public:
    void addPlayer(Player);
    void setBoard(unsigned int);
    void insertNewTile(QPoint);
    void undo();
    Tile getTile(QPoint);   //vraci kamen pro danou souradnici
    TileCorner getTile(int);   //vraci kamen pro danou souradnici
    int genRand(unsigned int, unsigned int);
protected:
    //Tile generateTile();
};

#endif // BOARD

