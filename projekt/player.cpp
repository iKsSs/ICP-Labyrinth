/*
    Autor:      Jakub Pastuszek, xpastu00
    Projekt:    ICP-Labyrinth 2014/2015
    Datum:      Kveten 2015

    Popis:      implementace funkci pro reprezentaci hrace a jeho obsluhu

*/

#include "player.h"

Player::Player(void)
{
    Player::countNoName++;
    this->name="Player" + QString::number(Player::countNoName);
    this->points = 0;
    this->position.setX(0);
    this->position.setY(0);
}

Player::Player(QString name)
{
    this->name = name;
    this->points = 0;
    this->position.setX(0);
    this->position.setY(0);
}

Player::Player(QString name, QPoint position)
{
    this->name = name;
    this->points = 0;
    this->position = position;
}

void Player::setPosition(QPoint position)
{
    this->position = position;
}

QPoint Player::getPosition()
{
    return this->position;
}

void Player::setName(QString name)
{
    this->name = name;
}

void Player::setImage(){
    unsigned int sw;
    if(this->position.x() == 0 && this->position.y() == 0){ sw = 3; }
    else if(this->position.x() == 0 && this->position.y() != 0){ sw = 2; }
    else if(this->position.x() != 0 && this->position.y() == 0){ sw = 1; }
    else { sw = 4; }

    switch(sw){
        case 1: image.load("images/P-1.png"); break;
        case 2: image.load("images/P-2.png"); break;
        case 3: image.load("images/P-3.png"); break;
        case 4: image.load("images/P-4.png"); break;
    default: image.load("images/C.png");
    }
}

QPixmap Player::getImage(){
    return this->image;
}

QString Player::getName()
{
    return this->name;
}

unsigned int Player::getPoints()
{
    return this->points;
}

void Player::addPoints(unsigned int add)
{
    this->points += add;
}

void Player::run()
{

}

bool Player::operator ==(const Player& p) const
{
    if (this->name == p.name)
        return true;
    else
        return false;
}

unsigned int Player::countNoName = 0;
