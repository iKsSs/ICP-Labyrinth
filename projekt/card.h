/**
 * @file       card.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Hlavicky funkci pro zobrazeni pokladu a hracich karet a jejich tridy
 */

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

    ~TreasurePack();
};

#endif // CARD

