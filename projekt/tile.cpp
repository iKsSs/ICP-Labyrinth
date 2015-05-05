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

QImage Tile::getImage(){
    return image;
}

int Tile::getMove(){
    return move;
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
