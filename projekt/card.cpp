#include "card.h"

Treasure::Treasure(unsigned int code){
    this->code = code;
}

TreasurePack::TreasurePack(unsigned int quantity){
    this->quantity = quantity;
    this->setTreasurePack();
}

void TreasurePack::setTreasurePack(){
    unsigned int code = 0;
    unsigned int i;
    for (i=0; i < this->quantity; ++i){
        Treasure x = Treasure(code);
        ++code;
        this->treasures.push_back(x);
    }
}

Treasure TreasurePack::getTreasure(){
    return this->treasures.first();
}
