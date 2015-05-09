/*
    Autor:      Jakub Pastuszek, xpastu00
    Projekt:    ICP-Labyrinth 2014/2015
    Datum:      Kveten 2015

    Popis:      implementace funkci pro reprezentaci hraci desky a jeji obsluhu; trida take implementuje
                zobrazovani hracu, vkladaneho kamene, hraci karty a stav hry

*/

#include "board.h"

Board::Board(): newTile{NULL}, treasures{NULL}, cards{NULL}, size{0} {}

void Board::setBoard(unsigned int n){
    unsigned int High = 3;
    unsigned int Low = 1;
    unsigned int tileType, tileRotation;
    unsigned int i, j, size;
    unsigned int StraightMax, CornerMax, CrossMax;
    unsigned int lackOfCorner=4, lackOfCross=4;

    this->size = n;

    size = n*n;

    switch(n){
        case 11: lackOfCross += 4;
        case 9:  lackOfCross += 4;
        case 7:  lackOfCross += 4;
    }

    StraightMax = CornerMax = CrossMax = (size/3);
    if(size%3){
        switch(this->genRand(Low, High)){
            case 1:
                ++StraightMax; break;
            case 2:
                ++CornerMax; break;
            case 3:
                ++CrossMax; break;
        default:
            ;
        }
    }

    for (i=0; i<n; ++i){
      for (j=0; j<n; ++j){

        Tile* x;
        if (i == 0 && j == 0){  //LH roh
            x = new TileCorner(4);
            --lackOfCorner;
        }
        else if (i == 0 && j == (n-1)){ //PH roh
            x = new TileCorner(3);
            --lackOfCorner;
        }
        else if (i == (n-1) && j == 0){ //LS roh
            x = new TileCorner(1);
            --lackOfCorner;
        }
        else if (i == (n-1) && j == (n-1)){ //PS roh
            x = new TileCorner(2);
            --lackOfCorner;
        }
        else if (i == 0 && j%2==0){  //prvni radek liche sloupce - cislovani od 0
            x = new TileCross(3);
            --lackOfCross;
        }
        else if (i == (n-1) && j%2==0){  //posledni radek liche sloupce - cislovani od 0
            x = new TileCross(1);
            --lackOfCross;
        }
        else if (i%2 == 0 && j == 0){  //prvni sloupec liche radky - cislovani od 0
            x = new TileCross(4);
            --lackOfCross;
        }
        else if (i%2 == 0 && j == (n-1)){  //posledni sloupec liche radky - cislovani od 0
            x = new TileCross(2);
            --lackOfCross;
        }
        else if (i==(size-1)){
            x = new TileCorner(2);
            --lackOfCross;
        }
        else{
            while(1){
                tileType = this->genRand(Low, High);
                tileRotation = this->genRand(Low, High);
                switch(tileType){
                    case 1:
                        if (StraightMax == TileStraight::count){continue;}
                        x = new TileStraight(tileRotation%2+1); break;
                    case 2:
                        if ((CornerMax - lackOfCorner) == TileCorner::count){continue;}
                        x = new TileCorner(tileRotation); break;
                    case 3:
                        if ((CrossMax - lackOfCross) == TileCross::count){continue;}
                        x = new TileCross(tileRotation); break;

                    default: x = NULL;
                }
                break;
            }
        }
        x->setPosition(QPoint(i,j));

        this->tiles.push_back(x);
    }
   }
}

void Board::setOutterFields(unsigned int n){
    unsigned int i;
    unsigned int count=0;    //pocet policek v jednom radku

    switch(n){
        case 11: count += 1;
        case 9: count += 1;
        case 7: count += 1;
        case 5: count += 2; break;
    default: count = 0;
    }
    count *= 4;     //mame 4 strany


    for (i=0; i<count; ++i){
        Tile* x = new TileOutter(0);
        this->outter.push_back(x);
    }
}

void Board::setTreasures(unsigned int n){
    this->treasures = new TreasurePack(n);
}

void Board::setCards(unsigned int n){
    this->cards = new TreasurePack(n);
}

void Board::setNewTile(void){
    unsigned int choice = this->genRand(1, 3);
    switch(choice){
        case 1:
            this->newTile = new TileStraight(1); break;
        case 2:
            this->newTile = new TileCorner(1); break;
        case 3:
            this->newTile = new TileCross(1); break;

        default: this->newTile = NULL;
    }
}

void Board::setSize(unsigned int size){
    this->size = size;
}

Tile* Board::getTile(int i){
    return this->tiles[i];
}

Tile* Board::getOutterField(unsigned int i){
    return this->outter[i];
}

Tile* Board::getNewTile(void){
    return this->newTile;
}

TreasurePack* Board::getTreasures(){
    return this->treasures;
}

TreasurePack* Board::getCards(){
    return this->cards;
}

void Board::addPlayer(Player play){
   this->players.push_back(play);
}

void Board::removePlayer(Player play){
    int n = this->players.size();
    for(int i = 0; i < n; ++i){
        if (this->players[i] == play){
            this->players.remove(i);
            break;
        }
    }
}

unsigned int Board::getNumPlayers(){
    return this->players.size();
}

Player Board::getPlayer(unsigned int i){
    return this->players[i];
}

void Board::setPlayerPos(){
    unsigned int i, n = this->players.size();
    for (i=0; i < n; ++i){
        switch(i){
            case 0: this->players[i].setPosition(QPoint(this->size-1,0)); break;
            case 1: this->players[i].setPosition(QPoint(0,this->size-1)); break;
            case 2: this->players[i].setPosition(QPoint(0,0)); break;
            case 3: this->players[i].setPosition(QPoint(this->size-1,this->size-1)); break;
        }
        this->players[i].setImage();
    }
}

int Board::genRand(unsigned int Low, unsigned int High){
    return qrand() % ((High + 1) - Low) + Low;
}

void Board::insertNewTile(QPoint point){
    unsigned int i, j;
    Tile* x;
    if(point.x() == this->size+1){
        j = this->size*this->size - (this->size+1-point.y());
        for(i=0; i < this->size; ++i){
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j -= this->size;
        }
    }
    if(point.x() == 0){
        j = point.y() - 1;
        for(i=0; i < this->size; ++i){
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j += this->size;
        }
    }
    if(point.y() == this->size+1){
        j = point.x()*this->size - 1;
        for(i=0; i < this->size; ++i){
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j -= 1;
        }
    }
    if(point.y() == 0){
        j = (point.x()-1)*this->size;
        for(i=0; i < this->size; ++i){
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j += 1;
        }
    }
}
