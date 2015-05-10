//ICP-Labyrinth 2014/2015
/**
 * @file       player.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Function headers for represenatation players in game.
 */

#ifndef PLAYER
#define PLAYER

#include <QPoint>
#include <QString>
#include <QImage>
#include <QPixmap>

#include "card.h"

/*! Class representing Player */

class Player
{
    QPoint position;
    QString name;
    QPixmap image;
    unsigned int points;
    Treasure* card;         //!< searched card(treasure) */
public:
    Player();
    Player(QString);      //!< constructor with name
    Player(QString, QPoint);     //!< constructor with name and position

    void setPosition(QPoint);
    void setPositionX(unsigned int);
    void setPositionY(unsigned int);

    QPoint getPosition();

    void setName(QString);
    void setImage(unsigned int);

    void setCard(Treasure*);
    Treasure* getCard();

    QPixmap getImage();
    QString getName();
    unsigned int getPoints();

    void addPoints(unsigned int);

    bool operator == (const Player&) const;   //!< operator to compare players name

    static unsigned int countNoName;    //!< auxiliary var for generating "noname palyer" */

    //~Player();

    QString toCSV();        //!< method to save data in file
};

#endif // PLAYER

