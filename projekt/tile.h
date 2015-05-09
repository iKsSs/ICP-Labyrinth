#ifndef TILE
#define TILE

#include <QPoint>
#include <QPixmap>
#include <QVector>

#include "player.h"

const bool T = true;
const bool F = false;

class Move{
    bool up;
    bool right;
    bool down;
    bool left;
public:
    Move(): up{false}, right{false}, down{false}, left{false} {};
    void setMove(bool up, bool right, bool down, bool left);
    unsigned int getMove();
};

class Tile{
protected:
  QPoint position;
  QPixmap image;
  Move move;
  unsigned int rotation;

public:
  Tile();
  Tile(unsigned int);    //kontruktor s rotaci
  virtual void rotate()=0;
  virtual void genImage()=0;

  void setPosition(QPoint);
  void setRotation(unsigned int);
  void setMove();

  QPoint getPosition();
  QPixmap getImage();
  Move getMove();   //treba zmenit navvratovy typ
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

