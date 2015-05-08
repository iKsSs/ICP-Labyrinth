#ifndef CARD
#define CARD

#include <QVector>
#include <QImage>

class CardPack{

  public:
    CardPack();
    CardPack(unsigned int);
    void setPack(unsigned int);
};

class Treasure{
    unsigned int code;
    QImage image;
  public:
    Treasure(){this->code=0;}
    Treasure(unsigned int);

};

class TreasurePack{
    unsigned int quantity;
    QVector<Treasure> treasures;
  public:
    TreasurePack(){this->quantity=0;}
    TreasurePack(unsigned int);
    void setTreasurePack();
    Treasure getTreasure();
    void shuffle();
};

class Card{

  public:
    Card();
    Card(unsigned int);
    void setCard(unsigned int);
};

#endif // CARD

