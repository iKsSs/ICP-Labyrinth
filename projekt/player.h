/**
 * @file       player.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Hlavicky funkci pro reprezentaci hrace ve hre
 */

#ifndef PLAYER
#define PLAYER

#include <QPoint>
#include <QString>
#include <QImage>
#include <QPixmap>

#include "card.h"

class Player
{
    QPoint position;
    QString name;
    QPixmap image;
    unsigned int points;
    Treasure* card;
public:
    Player();
    Player(QString);     //jmeno hráče
    Player(QString, QPoint position);     //jméno hráče a jeho výchozí pozice

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

    void run();

    bool operator == (const Player&) const;

    static unsigned int countNoName;

    //~Player();

    QString toCSV();
};

#endif // PLAYER

