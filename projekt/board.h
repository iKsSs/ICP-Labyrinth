/**
 * @file       board.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Hlavicky funkci pro zobrazeni hraci desky + trida uchovavajici cely stav hry
 */

#ifndef BOARD
#define BOARD

#include <QPoint>
#include <QVector>
#include <QSet>
#include <QTime>
#include <qglobal.h>

#include "player.h"
#include "tile.h"
#include "card.h"

class Board
{
    QVector<Tile*> tiles;
    QVector<Tile*> outter;
    QVector<Player*> players;
    Tile* newTile;
    unsigned int size;
    unsigned int act;

    TreasurePack* treasures;
    TreasurePack* cards;

    //...
    QVector<Board> board;
public:
    Board();
    void setBoard(unsigned int);
    void setOutterFields(unsigned int);
    void setTreasureToTile(unsigned int, unsigned int);
    void setCardToPlayers();
    void setTreasures(unsigned int);
    void setCards(unsigned int);
    void setNewTile(void);
    void setSize(unsigned int);

    void setPlayerPos();
    void recoverPlayerImage();

    //Tile* getTile(QPoint);   //vraci kamen pro danou souradnici
    Tile* getTile(int);     //vraci kamen pro dany index
    Tile* getOutterField(unsigned int);
    Tile* getNewTile(void); //vraci kamen mimo hraci plochu
    TreasurePack* getTreasures();
    TreasurePack* getCards();

    void addPlayer(Player *);
    void removePlayer(Player *);
    unsigned int getNumPlayers();
    Player* getPlayer(unsigned int);
    Player* getActPlayer();
    void actPlus();

    void insertNewTile(QPoint);
    void undo();
    QString data();
    void load(QString filename);

    void updatePlayersV(bool, bool, bool, bool, int);
    void updatePlayersH(bool, bool, bool, bool, int);

    int genRand(unsigned int, unsigned int);

    unsigned int state;

    static const unsigned int SHIFT = 1;
    static const unsigned int MOVE = 2;
    static const unsigned int STAY = 3;
protected:
    //Tile generateTile();
};

#endif // BOARD

