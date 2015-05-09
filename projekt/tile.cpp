/**
 * @file       tile.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Implementace funkci pro reprezentaci kamene a jeho obsluhu.
 */

#include "tile.h"

/**
 * @brief Move::Move
 *
 * Constructor with directions up, right, down and left
 */
Move::Move(): up{false}, right{false}, down{false}, left{false}
{}

/**
 * @brief Move::setMove
 * @param up
 * @param right
 * @param down
 * @param left
 *
 * Set directions up, right, down and left
 */
void Move::setMove(bool up, bool right, bool down, bool left){
    this->up = up;
    this->right = right;
    this->down = down;
    this->left = left;
}

/**
 * @brief Move::getMove
 * @return coded directions
 *
 * Get coded directions
 */
unsigned int Move::getMove(){
    unsigned int num=0;
    num += up    ? 1000 : 0;
    num += right ? 100 : 0;
    num += down  ? 10 : 0;
    num += left  ? 1 : 0;
    return num;
}

/**
 * @brief Move::moveUp
 * @return TRUE     up way opened
 * @return FALSE    up way closed
 *
 * Return if there is up way opened
 */
bool Move::moveUp()
{
    return this->up;
}

/**
 * @brief Move::moveRight
 * @return TRUE     right way opened
 * @return FALSE    right way closed
 *
 * Return if there is right way opened
 */
bool Move::moveRight()
{
    return this->right;
}

/**
 * @brief Move::moveDown
 * @return TRUE     down way opened
 * @return FALSE    down way closed
 *
 * Return if there is down way opened
 */
bool Move::moveDown()
{
    return this->down;
}

/**
 * @brief Move::moveLeft
 * @return TRUE     left way opened
 * @return FALSE    left way closed
 *
 * Return if there is left way opened
 */
bool Move::moveLeft()
{
    return this->left;
}

/**
 * @brief Tile::Tile
 *
 * Implicit constructor
 */
Tile::Tile(){
    this->rotation = 1;
    this->treasure = NULL;
}

/**
 * @brief Tile::Tile
 * @param r
 *
 * Constructor with rotation
 */
Tile::Tile(unsigned int r){
    this->rotation = r;
    this->treasure = NULL;
}

/**
 * @brief Tile::setPosition
 * @param pos
 *
 * Set position
 */
void Tile::setPosition(QPoint pos){
    this->position = pos;
}

/**
 * @brief Tile::setRotation
 * @param r
 *
 * Set rotation
 */
void Tile::setRotation(unsigned int r){
    this->rotation = r;
}

/**
 * @brief Tile::setTreasure
 *
 * Set treasure
 */
void Tile::setTreasure(Treasure *t){
    this->treasure = t;
    this->treasure->setImage();
}

/**
 * @brief Tile::getPosition
 * @return position
 *
 * Get position
 */
QPoint Tile::getPosition(){
    return this->position;
}

/**
 * @brief Tile::getImage
 * @return image
 *
 * Get image
 */
QPixmap Tile::getImage(){
    return this->image;
}

/**
 * @brief Tile::getMove
 * @return move
 *
 * Get move
 */
Move Tile::getMove(){
    return this->move;
}

/**
 * @brief getTreasure
 * @return treasure
 *
 * Return treasure
 */
Treasure* Tile::getTreasure(){
    return this->treasure;
}

/**
 * @brief Tile::getRotation
 * @return rotation
 *
 * Get rotation
 */
unsigned int Tile::getRotation(){
    return this->rotation;
}

/**
 * @brief TileStraight::TileStraight
 * @param r
 *
 * Constructor with rotation
 */
TileStraight::TileStraight(unsigned int r){
    TileStraight::count++;
    this->rotation = r;
    this->setMove();
    this->genImage();
}

/**
 * @brief TileCorner::TileCorner
 * @param r
 *
 * Constructor with rotation
 */
TileCorner::TileCorner(unsigned int r){
    TileCorner::count++;
    this->rotation = r;
    this->setMove();
    this->genImage();
}

/**
 * @brief TileCross::TileCross
 * @param r
 *
 * Constructor with rotation
 */
TileCross::TileCross(unsigned int r){
    TileCross::count++;
    this->rotation = r;
    this->setMove();
    this->genImage();
}

/**
 * @brief TileStraight::rotate
 *
 * Rotate tile, update move and gen image
 */
void TileStraight::rotate(){
    this->rotation++;
    if(this->rotation%3 == 0){this->rotation = 1;}
    this->setMove();
    this->genImage();
}

/**
 * @brief TileCorner::rotate
 *
 * Rotate tile, update move and gen image
 */
void TileCorner::rotate(){
    this->rotation++;
    if(this->rotation%5 == 0){this->rotation = 1;}
    this->setMove();
    this->genImage();
}

/**
 * @brief TileCross::rotate
 *
 * Rotate tile, update move and gen image
 */
void TileCross::rotate(){
    this->rotation++;
    if(this->rotation%5 == 0){this->rotation = 1;}
    this->setMove();
    this->genImage();
}

/**
 * @brief TileStraight::genImage
 *
 * Generate image
 */
void TileStraight::genImage()
{
    switch(this->rotation){
        case 1: this->image.load("images/S-1.png");break;
        case 2: this->image.load("images/S-2.png");break;
        default: this->image.load("images/C.png");
    }
}

/**
 * @brief TileCorner::genImage
 *
 * Generate image
 */
void TileCorner::genImage()
{
    switch(this->rotation){
        case 1: this->image.load("images/L-1.png");break;
        case 2: this->image.load("images/L-2.png");break;
        case 3: this->image.load("images/L-3.png");break;
        case 4: this->image.load("images/L-4.png");break;
        default: this->image.load("images/C.png");
    }
}

/**
 * @brief TileCross::genImage
 *
 * Generate image
 */
void TileCross::genImage()
{
    switch(this->rotation){
        case 1: this->image.load("images/T-1.png");break;
        case 2: this->image.load("images/T-2.png");break;
        case 3: this->image.load("images/T-3.png");break;
        case 4: this->image.load("images/T-4.png");break;
        default: this->image.load("images/C.png");
    }
}

/**
 * @brief TileStraight::setMove
 *
 * Set move
 */
void TileStraight::setMove()
{
    switch(this->rotation){
        case 1: move.setMove(F,T,F,T); break;
        case 2: move.setMove(T,F,T,F); break;
    }
}

/**
 * @brief TileCorner::setMove
 *
 * Set move
 */
void TileCorner::setMove()
{
    switch(this->rotation){
        case 1: move.setMove(T,T,F,F); break;
        case 2: move.setMove(T,F,F,T); break;
        case 3: move.setMove(F,F,T,T); break;
        case 4: move.setMove(F,T,T,F); break;
    }
}

/**
 * @brief TileCross::setMove
 *
 * Set move
 */
void TileCross::setMove()
{
    switch(this->rotation){
        case 1: move.setMove(T,T,F,T); break;
        case 2: move.setMove(T,F,T,T); break;
        case 3: move.setMove(F,T,T,T); break;
        case 4: move.setMove(T,T,T,F); break;
    }
}

/**
 * @brief TileOutter::TileOutter
 * @param r
 *
 * Constructor with rotation
 */
TileOutter::TileOutter(unsigned int r){
    this->rotation = r;
    this->genImage();
}

/**
 * @brief TileOutter::genImage
 *
 * Generate image
 */
void TileOutter::genImage()
{
   this->image.load("images/E.png");
}

//inicializace statickych promennych
unsigned int TileStraight::count = 0;
unsigned int TileCorner::count = 0;
unsigned int TileCross::count = 0;
