//ICP-Labyrinth 2014/2015
/**
 * @file       tile.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Function headers for represenatation tile in game as has the main and linkable fields around game board, and
 * tile outside of board for insert. Class representing possible outbound paths from tile. Every type of tile has
 * a separate class.
 */

#ifndef TILE
#define TILE

#include <QPixmap>
#include <QVector>
#include <QString>

#include "player.h"
#include "card.h"

const bool T = true;
const bool F = false;

/*! Class representing possible ways out of Tile */

class Move{
    bool up;        //!< way up */
    bool right;     //!< way right */
    bool down;      //!< way down */
    bool left;      //!< way left */
public:
    Move();
    void setMove(bool, bool, bool, bool);
    unsigned int getMove();     //!< get coded move
    bool moveUp();
    bool moveRight();
    bool moveDown();
    bool moveLeft();
};

/*! Class representing Tile - abstract class */

class Tile{
protected:
  QPoint position;
  QPixmap image;
  Move move;
  Treasure *treasure;
  unsigned int rotation;

public:
  Tile();
  Tile(unsigned int);       //!< constructor with rotation
  virtual void rotate()=0;
  virtual void genImage()=0;

  void setPosition(QPoint);
  void setRotation(unsigned int);
  void setMove();
  void setTreasure(Treasure*);

  void removeTreasure();

  QPoint getPosition();
  QPixmap getImage();
  Move getMove();
  Treasure* getTreasure();
  unsigned int getRotation();

  void addPlayer(Player);
  void removePlayer(Player);
  QVector<Player> getPlayers();

  QString toCSV();          //!< method to data game in file
};

/*! Class representing straight Tile */

class TileStraight: public Tile{

public:
    static unsigned int count;
  TileStraight(unsigned int);    //!< constructor with rotation
  TileStraight(){TileStraight::count++;}
  virtual void rotate();
  virtual void genImage();
  void setMove();
};

/*! Class representing corner Tile */

class TileCorner: public Tile{

public:
    static unsigned int count;
  TileCorner(unsigned int);    //!< constructor with rotation
  TileCorner(){TileCorner::count++;}
  virtual void rotate();
  virtual void genImage();
  void setMove();
};

/*! Class representing cross Tile */

class TileCross: public Tile{

public:
    static unsigned int count;
  TileCross(unsigned int);    //!< constructor with rotation
  TileCross(){TileCross::count++;}
  virtual void rotate();
  virtual void genImage();
  void setMove();
};

/*! Class representing outter Tile */

class TileOutter: public Tile{

public:
  TileOutter(unsigned int);    //!< constructor with rotation
  TileOutter(){}
  virtual void rotate(){}
  virtual void genImage();
};

#endif // TILE

