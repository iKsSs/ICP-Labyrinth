/**
 * @file       card.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Implementace funkci pro reprezentaci pokladu a hracich karet a jejich obsluhu
 */

#include "card.h"

/**
 * @brief Treasure::Treasure
 * @param code
 *
 * Constructor with code
 */
Treasure::Treasure(unsigned int code){
    this->code = code;
}

/**
 * @brief Treasure::getCode
 * @return code
 *
 * Return code of treasure
 */
unsigned int Treasure::getCode(){
    return this->code;
}

/**
 * @brief TreasurePack::TreasurePack
 * @param quantity
 *
 * Constructor with quantity
 */
TreasurePack::TreasurePack(unsigned int quantity){
    this->quantity = quantity;
    this->setTreasurePack();
}

/**
 * @brief TreasurePack::setTreasurePack
 *
 * Set pack of treasures
 */
void TreasurePack::setTreasurePack(){
    unsigned int code = 0;
    unsigned int i;
    for (i=0; i < this->quantity; ++i){ //pocet pokladu je quantity
        Treasure *x = new Treasure(code);
        ++code;
        this->treasures.push_back(x);
    }
}

/**
 * @brief TreasurePack::getTreasure
 * @return treasure on first index
 *
 * Return first index of treasure
 */
Treasure* TreasurePack::getTreasure(){
    return this->treasures.first();
}

/**
 * @brief TreasurePack::getTreasure
 * @param i
 * @return treasure on index i
 *
 * Return i index of treasure
 */
Treasure* TreasurePack::getTreasure(unsigned int i){
    return this->treasures[i];
}

/**
 * @brief TreasurePack::shuffle
 *
 * Shuffle treasures in package
 */
void TreasurePack::shuffle(){
    unsigned int i, random;
    Treasure *pom;
    for (i=0; i < quantity; ++i){
        random = qrand() % this->treasures.count();
        //zameneni pokladu na indexech i a random
        pom = this->treasures[i];
        this->treasures[i] = this->treasures[random];
        this->treasures[random] = pom;
    }
}

/**
 * @brief TreasurePack::~TreasurePack
 *
 * Implicit destructor
 */
TreasurePack::~TreasurePack(){
    unsigned int i;
    for (i=0; i < this->quantity; ++i){ //uvolni vsechny poklady
        delete this->treasures[i];
    }
}
