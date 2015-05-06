#include "tile.h"

Tile::Tile(){
    rotation = 0;
    move = 0;
}

Tile::Tile(int r){
    rotation = r;
    move = 0;
}

void Tile::rotate(){
    rotation = (rotation+1)%4 + 1;
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
    rotation = (rotation+1)%2 + 1;
}

unsigned int TileStraight::count = 0;
unsigned int TileCorner::count = 0;
unsigned int TileCross::count = 0;

TileStraight::TileStraight(int r){
    TileStraight::count++;
    rotation = r;
    move = 2;

    switch(rotation){
        case 1: image.load("images/S-1.png");break;
        case 2: image.load("images/S-2.png");break;
        default: image.load("images/C.png");
    }
}

TileCorner::TileCorner(int r){
    TileCorner::count++;
    rotation = r;
    move = 2;

    switch(rotation){
        case 1: image.load("images/L-1.png");break;
        case 2: image.load("images/L-2.png");break;
        case 3: image.load("images/L-3.png");break;
        case 4: image.load("images/L-4.png");break;
        default: image.load("images/C.png");
    }
}

TileCross::TileCross(int r){
    TileCross::count++;
    rotation = r;
    move = 3;

    switch(rotation){
        case 1: image.load("images/T-1.png");break;
        case 2: image.load("images/T-2.png");break;
        case 3: image.load("images/T-3.png");break;
        case 4: image.load("images/T-4.png");break;
        default: image.load("images/C.png");
    }
}
