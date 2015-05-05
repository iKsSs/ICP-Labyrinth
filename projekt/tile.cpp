#include "tile.h"

Tile::Tile(){
    rotation = 0;
    move = 0;
}

void Tile::rotate(){
    rotation = (rotation+1)%4;
}

void Tile::setPosition(QPoint pos){
    this->position = pos;
}

QPoint Tile::getPosition(){
    return position;
}

int Tile::getMove(){
    return move;
}

void Tile::setRotation(int r){
    this->rotation = r;
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
    rotation = (rotation+1)%2;
}

QPixmap TileStraight::getImage(){
    switch(rotation){
        case 0: return QPixmap("images/S-1.png");
        case 1: return QPixmap("images/S-2.png");
        default: return QPixmap();
    }
}

QPixmap TileCorner::getImage(){
    switch(rotation){
        case 0: return QPixmap("images/L-1.png");
        case 1: return QPixmap("images/L-2.png");
        case 2: return QPixmap("images/L-3.png");
        case 3: return QPixmap("images/L-4.png");
        default: return QPixmap();
    }
}

QPixmap TileCross::getImage(){
    switch(rotation){
        case 0: return QPixmap("images/T-1.png");
        case 1: return QPixmap("images/T-2.png");
        case 2: return QPixmap("images/T-3.png");
        case 3: return QPixmap("images/T-4.png");
        default: return QPixmap();
    }
}

unsigned int TileStraight::count = 0;
unsigned int TileCorner::count = 0;
unsigned int TileCross::count = 0;
