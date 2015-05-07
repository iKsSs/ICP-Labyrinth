#include "player.h"
#include "tile.h"
#include <QPoint>
#include <QVector>
#include <QTime>
#include <qglobal.h>

#ifndef BOARD
#define BOARD

class Board
{
    QVector<Tile*> tiles;
    QVector<Tile*> outter;
    QVector<Player> players;
    Tile* newTile;

    //...
    QVector<Board> board;
public:
    void addPlayer(Player);
    void removePlayer(Player);
    int getNumPlayers();
    Player getPlayer(unsigned int);
    void setBoard(unsigned int);
    void setOutterFields(unsigned int);
    Tile* getOutterField(unsigned int);
    void insertNewTile(QPoint);
    void genNewTile(void);
    Tile* getNewTile(void); //vraci kamen mimo hraci plochu
    void undo();
    Tile* getTile(QPoint);   //vraci kamen pro danou souradnici
    Tile* getTile(int);     //vraci kamen pro dany index
    int genRand(unsigned int, unsigned int);
protected:
    //Tile generateTile();
};

#endif // BOARD

