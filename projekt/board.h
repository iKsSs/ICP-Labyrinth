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

#include <QVector>
#include <QTime>

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
    int act;   //!< num of active player */

    TreasurePack* treasures;
    TreasurePack* cards;

    unsigned int b_row, b_col;
    int b_type;

    //...
    QVector<QString> bckpList;  //!< backup state for undo */
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

    unsigned int getB_col();
    void setB_col(unsigned int);
    unsigned int getB_row();
    void setB_row(unsigned int);
    int getB_type();
    void setB_type(int);

    void insertNewTile(QPoint);
    QString data();
    void load(QString, QString);        //!< load game from file or string
    void makeBckp();
    void undo();

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

