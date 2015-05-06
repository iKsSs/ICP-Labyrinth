#include "board.h"

void Board::setBoard(unsigned int n){
    unsigned int High = 3;
    unsigned int Low = 1;
    unsigned int tileType, tileRotation;
    unsigned int i, j, size;
    unsigned int StraightMax, CornerMax, CrossMax;

    size = n*n;

    for (i=0; i<n; ++i){
      for (j=0; j<n; ++j){

        Tile* x;
        if (i == 0 && j == 0){  //LH roh
            x = new TileCorner(4);
        }
        else if (i == 0 && j == (n-1)){ //PH roh
            x = new TileCorner(3);
        }
        else if (i == (n-1) && j == 0){ //LS roh
            x = new TileCorner(1);
        }
        else if (i == (n-1) && j == (n-1)){ //PS roh
            x = new TileCorner(2);
        }
        else if (i == 0 && j%2==0){  //prvni radek liche sloupce - cislovani od 0
            x = new TileCross(3);
        }
        else if (i == (n-1) && j%2==0){  //posledni radek liche sloupce - cislovani od 0
            x = new TileCross(1);
        }
        else if (i%2 == 0 && j == 0){  //prvni sloupec liche radky - cislovani od 0
            x = new TileCross(4);
        }
        else if (i%2 == 0 && j == (n-1)){  //posledni sloupec liche radky - cislovani od 0
            x = new TileCross(2);
        }
        else if (i==(size-1)){
            x = new TileCorner(2);
        }
        else{
            tileType = this->genRand(Low, High);
            tileRotation = this->genRand(Low, High);
            switch(tileType){
                case 1: x = new TileStraight(tileRotation%2+1); break;
                case 2: x = new TileCorner(tileRotation); break;
                case 3: x = new TileCross(tileRotation); break;
            default: x = NULL;
            }
        }
        x->setPosition(QPoint(i,j));

        tiles.push_back(x);
    }
   }
}

Tile* Board::getTile(int i){
    return tiles[i];
}

int Board::genRand(unsigned int Low, unsigned int High){
    //qsrand(qrand());
    for (int i =0; i<10000000;i++);
    qsrand(QTime::currentTime().msec());
    return qrand() % ((High + 1) - Low) + Low;
}
