#include "player.h"
#include "tile.h"
#include <QPoint>
#include <QVector>

#ifndef BOARD
#define BOARD

class Board
{
    QVector<Tile> tiles;
    QVector<Player> players;
    Tile newTile;

    //...
    QVector<Board> board;
public:
    void addPlayer(Player);
    void setBoard(unsigned int);
    void insertNewTile(QPoint);
    void undo();
protected:
    //Tile generateTile();
};

#endif // BOARD

