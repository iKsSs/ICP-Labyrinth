#ifndef TILE
#define TILE

#include <QPoint>
#include <QImage>
#include <QVector>

#include "player.h"

class Tile{
  QPoint position;
  QImage image;
  int move;
  int rotation;
  QVector<Player> players;

public:
  Tile();
  void rotate();
  void setPosition(QPoint);
  QPoint getPosition();
  QImage getImage();
  int getMove();   //treba zmenit navvratovy typ
  void addPlayer(Player);
  void removePlayer(Player);
  QVector<Player> getPlayers();
};

class TileStraight: public Tile{
;
};

class TileCorner: public Tile{
;
};

class TileCross: public Tile{
;
};

#endif // TILE

