/**
 * @file       tile.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Implementace funkci pro reprezentaci kamene a jeho obsluhu.
 */

#include "tile.h"

void Move::setMove(bool up, bool right, bool down, bool left){
    this->up = up;
    this->right = right;
    this->down = down;
    this->left = left;
}

unsigned int Move::getMove(){
    unsigned int num=0;
    num += up    ? 1000 : 0;
    num += right ? 100 : 0;
    num += down  ? 10 : 0;
    num += left  ? 1 : 0;
    return num;
}

bool Move::moveUp()
{
    return this->up;
}

bool Move::moveDown()
{
    return this->down;
}

bool Move::moveRight()
{
    return this->right;
}

bool Move::moveLeft()
{
    return this->left;
}

Tile::Tile(){
    this->rotation = 1;
}

Tile::Tile(unsigned int r){
    this->rotation = r;
}

void Tile::setPosition(QPoint pos){
    this->position = pos;
}

void Tile::setRotation(unsigned int r){
    this->rotation = r;
}

QPoint Tile::getPosition(){
    return this->position;
}

QPixmap Tile::getImage(){
    return this->image;
}

Move Tile::getMove(){
    return this->move;
}

unsigned int Tile::getRotation(){
    return this->rotation;
}

TileStraight::TileStraight(unsigned int r){
    TileStraight::count++;
    this->rotation = r;
    this->setMove();
    this->genImage();
}

TileCorner::TileCorner(unsigned int r){
    TileCorner::count++;
    this->rotation = r;
    this->setMove();
    this->genImage();
}

TileCross::TileCross(unsigned int r){
    TileCross::count++;
    this->rotation = r;
    this->setMove();
    this->genImage();
}

void TileStraight::rotate(){
    this->rotation++;
    if(this->rotation%3 == 0){this->rotation = 1;}
    this->setMove();
    this->genImage();
}

void TileCorner::rotate(){
    this->rotation++;
    if(this->rotation%5 == 0){this->rotation = 1;}
    this->setMove();
    this->genImage();
}

void TileCross::rotate(){
    this->rotation++;
    if(this->rotation%5 == 0){this->rotation = 1;}
    this->setMove();
    this->genImage();
}

void TileStraight::genImage()
{
    switch(this->rotation){
        case 1: this->image.load("images/S-1.png");break;
        case 2: this->image.load("images/S-2.png");break;
        default: this->image.load("images/C.png");
    }
}

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

void TileStraight::setMove()
{
    switch(this->rotation){
        case 1: move.setMove(F,T,F,T); break;
        case 2: move.setMove(T,F,T,F); break;
    }
}

void TileCorner::setMove()
{
    switch(this->rotation){
        case 1: move.setMove(T,T,F,F); break;
        case 2: move.setMove(T,F,F,T); break;
        case 3: move.setMove(F,F,T,T); break;
        case 4: move.setMove(F,T,T,F); break;
    }
}

void TileCross::setMove()
{
    switch(this->rotation){
        case 1: move.setMove(T,T,F,T); break;
        case 2: move.setMove(T,F,T,T); break;
        case 3: move.setMove(F,T,T,T); break;
        case 4: move.setMove(T,T,T,F); break;
    }
}

TileOutter::TileOutter(unsigned int r){
    this->rotation = r;
    this->genImage();
}

void TileOutter::genImage()
{
   this->image.load("images/E.png");
}

unsigned int TileStraight::count = 0;
unsigned int TileCorner::count = 0;
unsigned int TileCross::count = 0;
