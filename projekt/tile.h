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
  Tile(unsigned int);    //kontruktor s rotaci
  virtual void rotate()=0;
  virtual void genImage()=0;

  void setPosition(QPoint);
  void setRotation(unsigned int);

  QPoint getPosition();
  QPixmap getImage();
  unsigned int getMove();   //treba zmenit navvratovy typ
  unsigned int getRotation();

  void addPlayer(Player);
  void removePlayer(Player);
  QVector<Player> getPlayers();
};

class TileStraight: public Tile{

public:
    static unsigned int count;
  TileStraight(unsigned int);    //kontruktor s rotaci
  TileStraight(){TileStraight::count++;}
  virtual void rotate();
  void genImage();
};

class TileCorner: public Tile{

public:
    static unsigned int count;
  TileCorner(unsigned int);    //kontruktor s rotaci
  TileCorner(){TileCorner::count++;}
  virtual void rotate();
  virtual void genImage();
};

class TileCross: public Tile{

public:
    static unsigned int count;
  TileCross(unsigned int);    //kontruktor s rotaci
  TileCross(){TileCross::count++;}
  virtual void rotate();
  virtual void genImage();
};

class TileOutter: public Tile{

public:
  TileOutter(unsigned int);    //kontruktor s rotaci
  TileOutter(){}
  virtual void rotate(){}
  virtual void genImage();
};

#endif // TILE

