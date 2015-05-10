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
#include <QPixmap>

class Treasure{
    unsigned int code;
    QPixmap image;
  public:
    Treasure();
    Treasure(unsigned int);
    unsigned int getCode();
    void setImage();
    QPixmap getImage();

    QString toCSV();
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
    void removeTreasure();
    void shuffle();
    void setVector(QVector<Treasure*>);

    QString toCSV(bool);

    ~TreasurePack();
};

#endif // CARD

