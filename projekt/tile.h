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
  void rotate();
  void setPosition(QPoint);
  QPoint getPosition();
  QPixmap getImage();
  void setRotation(int);
  int getMove();   //treba zmenit navvratovy typ
  void addPlayer(Player);
  void removePlayer(Player);
  QVector<Player> getPlayers();
};

class TileStraight: public Tile{
    static unsigned int count;
public:
  TileStraight(){TileStraight::count++;}
  void rotate();
  QPixmap getImage();
};

class TileCorner: public Tile{
    static unsigned int count;
public:
    TileCorner(){TileCorner::count++;}
  QPixmap getImage();
};

class TileCross: public Tile{
    static unsigned int count;
public:
    TileCross(){TileCross::count++;}
  QPixmap getImage();
};

#endif // TILE

