//ICP-Labyrinth 2014/2015
/**
 * @file       card.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Function headers for show treasures and cards plus their classes.
 */

#ifndef CARD
#define CARD

#include <QVector>
#include <QPixmap>

/*! Class representing treasure */

class Treasure{
    unsigned int code;
    QPixmap image;
  public:
    Treasure();
    Treasure(unsigned int);     //!< constructor with code
    unsigned int getCode();
    void setImage();
    QPixmap getImage();

    QString toCSV();        //!< method to save data in file
};

/*! Class representing pack of treasures */

class TreasurePack{
    unsigned int quantity;
    QVector<Treasure*> treasures;
  public:
    TreasurePack(){this->quantity=0;}
    TreasurePack(unsigned int);     //!< constructor with quantity
    void setTreasurePack();
    Treasure* getTreasure();        //!< get first treasure
    Treasure* getTreasure(unsigned int);    //!< get i-th treasure
    void removeTreasure();          //!< remove first treasure
    void shuffle();
    void setVector(QVector<Treasure*>);

    QString toCSV(bool);    //!< method to save game in file

    ~TreasurePack();
};

#endif // CARD

