#include "tile.h"

Tile::Tile(){
    rotation = 0;
    move = 0;
}

void Tile::rotate(){
;
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
    this->players.push_back(play);
}

void Tile::removePlayer(Player play){
    ;//najde hrace a vymaze ho z vektoru
}

QVector<Player> Tile::getPlayers(){
    return players;
}
