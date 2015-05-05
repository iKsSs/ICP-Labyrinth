#include "board.h"

void Board::setBoard(unsigned int n){
    int High = 3;
    int Low = 1;
    int tileType, tileRotation;
    int i, size;
    int StraightMax, CornerMax, CrossMax;

    size = n*n;

    for (i=0; i<size; ++i){
        if (i==0){
            TileCorner x;
            x.setRotation(3);
            tiles.push_back(x);
        }
        if (i==(n-1)){
            TileCorner x;
            x.setRotation(2);
            tiles.push_back(x);
        }
        if (i==(size-n)){
            TileCorner x;
            x.setRotation(0);
            tiles.push_back(x);
        }
        if (i==(size-1)){
            TileCorner x;
            x.setRotation(1);
            tiles.push_back(x);
        }
 /*       tileType = this->genRand(Low, High);

       // TileStraight::count;
        switch (tileType){
            case 1:break;
        }

        tileRotation = this->genRand(Low, High);*/
    }
}

TileCorner Board::getTile(int i){
    return tiles[i];
}

int Board::genRand(unsigned int Low, unsigned int High){
    qsrand(qrand());
    return qrand() % ((High + 1) - Low) + Low;
}
