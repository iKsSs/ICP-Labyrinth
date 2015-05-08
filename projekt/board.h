#ifndef BOARD
#define BOARD

#include <QPoint>
#include <QVector>
#include <QTime>
#include <qglobal.h>

#include "player.h"
#include "tile.h"
#include "card.h"

class Board
{
    QVector<Tile*> tiles;
    QVector<Tile*> outter;
    QVector<Player> players;
    Tile* newTile;

    //...
    QVector<Board> board;
public:
    void setBoard(unsigned int);
    void setOutterFields(unsigned int);
    void setNewTile(void);

    //Tile* getTile(QPoint);   //vraci kamen pro danou souradnici
    Tile* getTile(int);     //vraci kamen pro dany index
    Tile* getOutterField(unsigned int);
    Tile* getNewTile(void); //vraci kamen mimo hraci plochu

    void addPlayer(Player);
    void removePlayer(Player);
    unsigned int getNumPlayers();
    Player getPlayer(unsigned int);

    void insertNewTile(QPoint);
    void undo();

    int genRand(unsigned int, unsigned int);
protected:
    //Tile generateTile();
};

#endif // BOARD

