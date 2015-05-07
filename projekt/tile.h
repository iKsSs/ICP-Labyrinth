#ifndef TILE
#define TILE

#include <QPoint>
#include <QPixmap>
#include <QVector>

#include "player.h"

class Tile{
protected:
  QPoint position;
  QPixmap image;
  int move;
  int rotation;

public:
  Tile();
  Tile(int);    //kontruktor s rotaci
  virtual void rotate()=0;
  void setPosition(QPoint);
  QPoint getPosition();
  QPixmap getImage();
  void setRotation(int);
  int getRotation();
  int getMove();   //treba zmenit navvratovy typ
  void addPlayer(Player);
  void removePlayer(Player);
  QVector<Player> getPlayers();
  void genImage();
};

class TileStraight: public Tile{

public:
    static unsigned int count;
  TileStraight(int);    //kontruktor s rotaci
  TileStraight(){TileStraight::count++;}
  virtual void rotate();
  void genImage();
};

class TileCorner: public Tile{

public:
    static unsigned int count;
  TileCorner(int);    //kontruktor s rotaci
  TileCorner(){TileCorner::count++;}
  virtual void rotate();
  void genImage();
};

class TileCross: public Tile{

public:
    static unsigned int count;
  TileCross(int);    //kontruktor s rotaci
  TileCross(){TileCross::count++;}
  virtual void rotate();
  void genImage();
};

#endif // TILE

