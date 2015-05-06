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
  QVector<Player> players;

public:
  Tile();
  Tile(int);    //kontruktor s rotaci
  void rotate();
  void setPosition(QPoint);
  QPoint getPosition();
  QPixmap getImage();
  void setRotation(int);
  int getRotation();
  int getMove();   //treba zmenit navvratovy typ
  void addPlayer(Player);
  void removePlayer(Player);
  QVector<Player> getPlayers();
};

class TileStraight: public Tile{

public:
    static unsigned int count;
  TileStraight(int);    //kontruktor s rotaci
  TileStraight(){TileStraight::count++;}
  void rotate();
};

class TileCorner: public Tile{

public:
    static unsigned int count;
  TileCorner(int);    //kontruktor s rotaci
  TileCorner(){TileCorner::count++;}
};

class TileCross: public Tile{

public:
    static unsigned int count;
  TileCross(int);    //kontruktor s rotaci
  TileCross(){TileCross::count++;}
};

#endif // TILE

