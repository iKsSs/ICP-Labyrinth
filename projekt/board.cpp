/**
 * @file       board.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Implementace funkci pro reprezentaci hraci desky a jeji obsluhu; trida take implementuje
 * zobrazovani hracu, vkladaneho kamene, hraci karty a stav hry,
 */

#include "board.h"

/**
 * @brief Board::Board
 *
 * Implicit contrusctor
 */
Board::Board(): newTile{NULL}, treasures{NULL}, cards{NULL}, size{0} {}

/**
 * @brief Board::setBoard
 * @param n
 *
 * Set board
 */
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

/**
 * @brief Board::setOutterFields
 * @param n
 *
 * Set outter fields
 */
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

    for (i=0; i<count; ++i){    //vytvorim vektor policek
        Tile* x = new TileOutter(0);
        this->outter.push_back(x);
    }
}

/**
 * @brief Board::setTreasures
 * @param n
 *
 * Set treasure pack
 */
void Board::setTreasures(unsigned int n){
    this->treasures = new TreasurePack(n);
}

/**
 * @brief Board::setCards
 * @param n
 *
 * Set card pack
 */
void Board::setCards(unsigned int n){
    this->cards = new TreasurePack(n);
}

/**
 * @brief Board::setNewTile
 *
 * Set new tile out of board
 */
void Board::setNewTile(void){
    unsigned int choice = this->genRand(1, 3);
    switch(choice){
        case 1:
            this->newTile = new TileStraight(1); break;
        case 2:
            this->newTile = new TileCorner(1); break;
        case 3:
            this->newTile = new TileCross(1); break;
    }
}

/**
 * @brief Board::setSize
 * @param size
 *
 * Set board size
 */
void Board::setSize(unsigned int size){
    this->size = size;
}

/**
 * @brief Board::getTile
 * @param i
 * @return tile on index i
 *
 * Get tile on index i
 */
Tile* Board::getTile(int i){
    return this->tiles[i];
}

/**
 * @brief Board::getOutterField
 * @param i
 * @return outter tile on index i
 *
 * Get outter tile on index i
 */
Tile* Board::getOutterField(unsigned int i){
    return this->outter[i];
}

/**
 * @brief Board::getNewTile
 * @return new tile
 *
 * Get new tile
 */
Tile* Board::getNewTile(void){
    return this->newTile;
}

/**
 * @brief Board::getTreasures
 * @return reference to treasures
 *
 * Return reference to treasures
 */
TreasurePack* Board::getTreasures(){
    return this->treasures;
}

/**
 * @brief Board::getCards
 * @return reference to cards
 *
 * Return reference to cards
 */
TreasurePack* Board::getCards(){
    return this->cards;
}

/**
 * @brief Board::addPlayer
 * @param play
 *
 * Add new player to vector players
 */
void Board::addPlayer(Player* play){
   this->players.push_back(play);
}

/**
 * @brief Board::removePlayer
 * @param play
 *
 * Remove player from vector players
 */
void Board::removePlayer(Player* play){
    int n = this->players.size();
    for(int i = 0; i < n; ++i){
        if (this->players[i] == play){
            this->players.remove(i);
            break;
        }
    }
}

/**
 * @brief Board::getNumPlayers
 * @return size of vector players
 *
 * Return size of vector players
 */
unsigned int Board::getNumPlayers(){
    return this->players.size();
}

/**
 * @brief Board::getPlayer
 * @param i
 * @return reference to player on index i
 *
 * Return reference to player on index i in vector players
 */
Player *Board::getPlayer(unsigned int i){
    return this->players[i];
}

/**
 * @brief Board::setPlayerPos
 *
 * Set player position
 */
void Board::setPlayerPos(){
    unsigned int i, n = this->players.size();
    for (i=0; i < n; ++i){  //pro kazdeho hrace se nastavi pozice
        switch(i){
            case 0: this->players[i]->setPosition(QPoint(this->size-1,0)); break;
            case 1: this->players[i]->setPosition(QPoint(0,this->size-1)); break;
            case 2: this->players[i]->setPosition(QPoint(0,0)); break;
            case 3: this->players[i]->setPosition(QPoint(this->size-1,this->size-1)); break;
        }
        this->players[i]->setImage();    //podle pozice se nastavi obrazek
    }
}

/**
 * @brief Board::genRand
 * @param Low
 * @param High
 * @return generated number
 *
 * Generate number in interval <Low, High>
 */
int Board::genRand(unsigned int Low, unsigned int High){
    return qrand() % ((High + 1) - Low) + Low;
}

/**
 * @brief Board::insertNewTile
 * @param point
 *
 * Insert new tile into board and shift row or col
 */
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
