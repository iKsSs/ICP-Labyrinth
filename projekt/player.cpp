//ICP-Labyrinth 2014/2015
/**
 * @file       player.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Implementation of functions for representation player and its handle.
 */

#include "player.h"

/**
 * @brief Player::Player
 *
 * Implicit contructor - set name PlayerX
 */
Player::Player(void)
{
    Player::countNoName++;
    this->name="Player" + QString::number(Player::countNoName);
    this->points = 0;
    this->position.setX(0);
    this->position.setY(0);
}

/**
 * @brief Player::Player
 * @param name
 *
 * Constructor witch name of player
 */
Player::Player(QString name)
{
    this->name = name;
    this->points = 0;
    this->position.setX(0);
    this->position.setY(0);
}

/**
 * @brief Player::Player
 * @param name
 * @param position
 *
 * Contructor with specified name and positon of player
 */
Player::Player(QString name, QPoint position)
{
    this->name = name;
    this->points = 0;
    this->position = position;
}

/**
 * @brief Player::setPosition
 * @param position
 *
 * Set player position
 */
void Player::setPosition(QPoint position)
{
    this->position = position;
}

/**
 * @brief Player::setPositionX
 * @param p
 *
 * Set position X
 */
void Player::setPositionX(unsigned int p){
    this->position.setX(p);
}

/**
 * @brief Player::setPositionY
 * @param p
 *
 * Set position Y
 */
void Player::setPositionY(unsigned int p){
    this->position.setY(p);
}

/**
 * @brief Player::getPosition
 * @return position
 *
 * Get player position
 */
QPoint Player::getPosition()
{
    return this->position;
}

/**
 * @brief Player::setName
 * @param name
 *
 * Set player name
 */
void Player::setName(QString name)
{
    this->name = name;
}

/**
 * @brief Player::setCard
 * @param t
 *
 * Set card
 */
void Player::setCard(Treasure* t){
    this->card = t;
}

/**
 * @brief Player::getCard
 * @return card
 *
 * Get card
 */
Treasure* Player::getCard(){
    return this->card;
}

/**
 * @brief Player::getName
 * @return name
 *
 * Return name of player
 */
QString Player::getName()
{
    return this->name;
}

/**
 * @brief Player::getPoints
 * @return points
 *
 * Return points of player
 */
unsigned int Player::getPoints()
{
    return this->points;
}

/**
 * @brief Player::addPoints
 * @param add
 *
 * Add points to player
 */
void Player::addPoints(unsigned int add)
{
    this->points += add;
}

/**
 * @brief Player::operator ==
 * @param p
 * @return TRUE     Are equal
 * @return FALSE    Are NOT equal
 *
 * Compare players by name
 */
bool Player::operator ==(const Player& p) const
{
    if (this->name == p.name)
        return true;
    else
        return false;
}

/**
 * @brief Player::toCSV
 * @return csv
 *
 * Save state to csv file
 */
QString Player::toCSV()
{
    //vrati retezec CSV formatu pro player

    QString csv = "";
    csv.append("P;");
    csv.append(QString::number(this->position.x()) + ";");
    csv.append(QString::number(this->position.y()) + ";");
    csv.append(QString::number(this->points) + ";");
    csv.append(this->name + ";");
    csv.append(this->card->toCSV() + "\n");

    return csv;
}

//inicializace staticke promenne
unsigned int Player::countNoName = 0;
