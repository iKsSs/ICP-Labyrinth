#include "tile.h"

Tile::Tile(){
    rotation = 1;
    move = 0;
}

Tile::Tile(unsigned int r){
    rotation = r;
    move = 0;
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

unsigned int Tile::getMove(){
    return this->move;
}

unsigned int Tile::getRotation(){
    return this->rotation;
}

TileStraight::TileStraight(unsigned int r){
    TileStraight::count++;
    this->rotation = r;
    this->move = 2;

    this->genImage();
}

TileCorner::TileCorner(unsigned int r){
    TileCorner::count++;
    this->rotation = r;
    this->move = 2;

    this->genImage();
}

TileCross::TileCross(unsigned int r){
    TileCross::count++;
    this->rotation = r;
    this->move = 3;

    this->genImage();
}

void TileStraight::rotate(){
    this->rotation++;
    if(this->rotation%3 == 0){this->rotation = 1;}
    genImage();
}

void TileCorner::rotate(){
    this->rotation++;
    if(this->rotation%5 == 0){this->rotation = 1;}
    genImage();
}

void TileCross::rotate(){
    this->rotation++;
    if(this->rotation%5 == 0){this->rotation = 1;}
    genImage();
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
