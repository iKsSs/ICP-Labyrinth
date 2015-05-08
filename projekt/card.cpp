#include "card.h"

Treasure::Treasure(unsigned int code){
    this->code = code;
}

unsigned int Treasure::getCode(){
    return this->code;
}

TreasurePack::TreasurePack(unsigned int quantity){
    this->quantity = quantity;
    this->setTreasurePack();
}

void TreasurePack::setTreasurePack(){
    unsigned int code = 0;
    unsigned int i;
    for (i=0; i < this->quantity; ++i){
        Treasure *x = new Treasure(code);
        ++code;
        this->treasures.push_back(x);
    }
}

Treasure* TreasurePack::getTreasure(){
    return this->treasures.first();
}

Treasure* TreasurePack::getTreasure(unsigned int i){
    return this->treasures[i];
}

void TreasurePack::shuffle(){
    unsigned int i, random;
    Treasure *pom;
    for (i=0; i < quantity; ++i){
        random = qrand() % this->treasures.count();
        pom = this->treasures[i];
        this->treasures[i] = this->treasures[random];
        this->treasures[random] = pom;
    }
}
