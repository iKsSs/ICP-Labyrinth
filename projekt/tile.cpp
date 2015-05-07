#include "tile.h"

Tile::Tile(){
    rotation = 1;
    move = 0;
}

Tile::Tile(int r){
    rotation = r;
    move = 0;
}

void Tile::setPosition(QPoint pos){
    this->position = pos;
}

QPoint Tile::getPosition(){
    return position;
}

QPixmap Tile::getImage(){
    return image;
}

int Tile::getMove(){
    return move;
}

void Tile::setRotation(int r){
    this->rotation = r;
}

int Tile::getRotation(){
    return rotation;
}


void Tile::addPlayer(Player play){
   players.push_back(play);
}

void Tile::removePlayer(Player play){
    int n = players.size();
    for(int i = 0; i < n; ++i){
        if (players[i] == play){
            players.remove(i);
            break;
        }
    }
}

QVector<Player> Tile::getPlayers(){
    return players;
}

void TileStraight::rotate(){
    rotation++;
    if(rotation%3 == 0){rotation = 1;}
    genImage();
}

void TileCorner::rotate(){
    rotation++;
    if(rotation%5 == 0){rotation = 1;}
    genImage();
}

void TileCross::rotate(){
    rotation++;
    if(rotation%5 == 0){rotation = 1;}
    genImage();
}

unsigned int TileStraight::count = 0;
unsigned int TileCorner::count = 0;
unsigned int TileCross::count = 0;

TileStraight::TileStraight(int r){
    TileStraight::count++;
    rotation = r;
    move = 2;

    genImage();
}

TileCorner::TileCorner(int r){
    TileCorner::count++;
    rotation = r;
    move = 2;

    genImage();
}

TileCross::TileCross(int r){
    TileCross::count++;
    rotation = r;
    move = 3;

    genImage();
}

void TileStraight::genImage()
{
    switch(rotation){
        case 1: image.load("images/S-1.png");break;
        case 2: image.load("images/S-2.png");break;
        default: image.load("images/C.png");
    }
}

void TileCorner::genImage()
{
    switch(rotation){
        case 1: image.load("images/L-1.png");break;
        case 2: image.load("images/L-2.png");break;
        case 3: image.load("images/L-3.png");break;
        case 4: image.load("images/L-4.png");break;
        default: image.load("images/C.png");
    }
}

void TileCross::genImage()
{
    switch(rotation){
        case 1: image.load("images/T-1.png");break;
        case 2: image.load("images/T-2.png");break;
        case 3: image.load("images/T-3.png");break;
        case 4: image.load("images/T-4.png");break;
        default: image.load("images/C.png");
    }
}
