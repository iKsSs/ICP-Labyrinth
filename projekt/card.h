#ifndef CARD
#define CARD

#include <QVector>
#include <QImage>

class Treasure{
    unsigned int code;
    QImage image;
  public:
    Treasure();
    Treasure(unsigned int);
    unsigned int getCode();
};

class TreasurePack{
    unsigned int quantity;
    QVector<Treasure*> treasures;
  public:
    TreasurePack(){this->quantity=0;}
    TreasurePack(unsigned int);
    void setTreasurePack();
    Treasure* getTreasure();
    Treasure* getTreasure(unsigned int);
    void shuffle();
};

#endif // CARD

