/**
 * @file       tile.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Hlavicky funkci pro reprezentaci kamene ve hre, jak jiz hlavniho pole, klikatelnych poli kolem hraciho pole,
 * tak i kamen mimo hraci desku; trida reprezentujici mozne odchozi cesty z kamene; kazdy druh kamene ma svou tridu
 */

#ifndef TILE
#define TILE

#include <QPoint>
#include <QPixmap>
#include <QVector>
#include <QString>

#include "player.h"
#include "card.h"

const bool T = true;
const bool F = false;

class Move{
    bool up;
    bool right;
    bool down;
    bool left;
public:
    Move();
    void setMove(bool, bool, bool, bool);
    unsigned int getMove();
    bool moveUp();
    bool moveRight();
    bool moveDown();
    bool moveLeft();
};

class Tile{
protected:
  QPoint position;
  QPixmap image;
  Move move;
  Treasure *treasure;
  unsigned int rotation;

public:
  Tile();
  Tile(unsigned int);    //kontruktor s rotaci
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

  QString toCSV();
};

class TileStraight: public Tile{

public:
    static unsigned int count;
  TileStraight(unsigned int);    //kontruktor s rotaci
  TileStraight(){TileStraight::count++;}
  virtual void rotate();
  virtual void genImage();
  void setMove();
};

class TileCorner: public Tile{

public:
    static unsigned int count;
  TileCorner(unsigned int);    //kontruktor s rotaci
  TileCorner(){TileCorner::count++;}
  virtual void rotate();
  virtual void genImage();
  void setMove();
};

class TileCross: public Tile{

public:
    static unsigned int count;
  TileCross(unsigned int);    //kontruktor s rotaci
  TileCross(){TileCross::count++;}
  virtual void rotate();
  virtual void genImage();
  void setMove();
};

class TileOutter: public Tile{

public:
  TileOutter(unsigned int);    //kontruktor s rotaci
  TileOutter(){}
  virtual void rotate(){}
  virtual void genImage();
};

#endif // TILE

