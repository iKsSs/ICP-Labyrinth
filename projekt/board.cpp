#include "board.h"

void Board::setBoard(unsigned int n){
    unsigned int High = 3;
    unsigned int Low = 1;
    unsigned int tileType, tileRotation;
    unsigned int i, j, size;
    unsigned int StraightMax, CornerMax, CrossMax;
    unsigned int lackOfCorner=4, lackOfCross=4;

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
            ++StraightMax;
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

        tiles.push_back(x);
    }
   }
}

void Board::genNewTile(void){
    int choice = this->genRand(1, 3);
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

Tile* Board::getNewTile(void){
    return this->newTile;
}

Tile* Board::getTile(int i){
    return tiles[i];
}

int Board::genRand(unsigned int Low, unsigned int High){
    return qrand() % ((High + 1) - Low) + Low;
}

void Board::addPlayer(Player play){
   players.push_back(play);
}

void Board::removePlayer(Player play){
    int n = players.size();
    for(int i = 0; i < n; ++i){
        if (players[i] == play){
            players.remove(i);
            break;
        }
    }
}

int Board::getNumPlayers(){
    return players.size();
}

Player Board::getPlayer(unsigned int i){
    return players[i];
}
