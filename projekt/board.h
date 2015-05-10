//ICP-Labyrinth 2014/2015
/**
 * @file       board.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Function headers for show game board and class hold whole state of game.
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

/*! Class representing game */

class Board
{
    QVector<Tile*> tiles;
    QVector<Tile*> outter;
    QVector<Player*> players;
    Tile* newTile;      //!< tile to insert */
    unsigned int size;  //!< game board size */
    unsigned int act;   //!< num of active player */

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

    unsigned int getSize();

    void setPlayerPos();
    void recoverPlayerImage();      //!< set player image after load

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
    void actPlus();         //!< change active player

    void insertNewTile(QPoint);
    void undo();                    //!< step backward
    QString data();
    void load(QString filename);        //!< load game from file

    void updatePlayersV(bool, bool, bool, bool, int);   //!< method to move player with tile vertically
    void updatePlayersH(bool, bool, bool, bool, int);   //!< method to move player with tile horizontally

    int genRand(unsigned int, unsigned int);        //!< random generator from Low to High

    unsigned int state;         //!< state in game (shift/move/stay)

    static const unsigned int SHIFT = 1;
    static const unsigned int MOVE = 2;
    static const unsigned int STAY = 3;
protected:
    //Tile generateTile();
};

#endif // BOARD

