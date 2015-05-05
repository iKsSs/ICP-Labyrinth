#include "player.h"

Player::Player()
{
    this->name="NoName Player";
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
    this->position.setX(0);
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
