//ICP-Labyrinth 2014/2015
/**
 * @file       board.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Implementation of functions for representation game board and its handle. Class implement
 * showing players, inserting tile, card and state of game too.
 */

#include "board.h"

#include <QFile>
#include <QTextStream>

/**
 * @brief Board::Board
 *
 * Implicit contructor
 */
Board::Board(){
    newTile = NULL;
    treasures = NULL;
    cards = NULL;
    size = 0;
    act = 0;
    state = 3;
    b_row = 100;
    b_col = 100;
    b_type = 0;
}

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
 * @brief Board::setTreasureToTile
 * @param n
 * @param q
 *
 * Set treasure to tile
 */
void Board::setTreasureToTile(unsigned int n, unsigned int q){
    unsigned int i, random, a = 0;
    unsigned int size = n*n;

    QVector<int> vec;
    for (i=0; i < size; ++i){
        vec.append(i);
    }

    for (a=0; a < q; ++a){
        random = qrand() % size;

        i = random % vec.size();

        this->getTile(vec[i])->setTreasure(this->treasures->getTreasure(a));

        vec.remove(i);
    }
}

/**
 * @brief Board::setCardToPlayers
 *
 * Set card to each player
 */
void Board::setCardToPlayers(){
    unsigned int i, n = this->players.size();
    for (i=0; i < n; ++i){
        this->players[i]->setCard(this->cards->getTreasure());
        //this->players[i]->getCard()->setImage();
        this->cards->removeTreasure();
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
 * @brief Board::getSize
 * @return size
 *
 * Return board size
 */
unsigned int Board::getSize(){
    return this->size;
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
 * @brief Board::getActPlayer
 * @return reference to player on turn
 *
 * Return reference to player on turn in vector players
 */
Player *Board::getActPlayer(){
    return this->players[act];
}

/**
 * @brief Board::getB_col
 * @return b_col
 *
 * Get b_col
 */
unsigned int Board::getB_col(){
    return this->b_col;
}

/**
 * @brief Board::setB_col
 * @param col
 *
 * Set b_col
 */
void Board::setB_col(unsigned int col){
    this->b_col = col;
}

/**
 * @brief Board::getB_row
 * @return b_row
 *
 * Get b_row
 */
unsigned int Board::getB_row(){
    return this->b_row;
}

/**
 * @brief Board::setB_row
 * @param row
 *
 * Set b_row
 */
void Board::setB_row(unsigned int row){
    this->b_row = row;
}

/**
 * @brief Board::getB_type
 * @return b_type
 *
 * Get b_type
 */
int Board::getB_type(){
    return this->b_type;
}

/**
 * @brief Board::getB_type
 * @param type
 *
 * Set b_type
 */
void Board::setB_type(int type){
    this->b_type = type;
}

/**
 * @brief Board::actPlus
 *
 * Shift activ token to next player
 */
void Board::actPlus(){
    ++act;
    if (act == this->players.size()){
        act = 0;
    }
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
    int i, j, k;
    int n = this->players.size();
    bool p_0, p_1, p_2, p_3;
    p_0 = p_1 = p_2 = p_3 = false;
    int size = static_cast<signed int>(this->size);

    Tile* x;
    //shift up
    if(point.x() == size+1){
        j = size*size - (size+1-point.y());
        for(i=0; i < size; ++i){
            //kontrola zda na aktualne se posouvajicim policku neni hrac
            for(k=0; k < n; ++k){
                if(this->getPlayer(k)->getPosition() == QPoint(i,point.y()-1)){
                    switch(k){
                        case 0: p_0 = true; break;
                        case 1: p_1 = true; break;
                        case 2: p_2 = true; break;
                        case 3: p_3 = true; break;
                    }
                }
            }
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j -= size;
        }

        this->updatePlayersV(p_0, p_1, p_2, p_3, -1);

    }
    //shift down
    else if(point.x() == 0){
        j = point.y() - 1;
        for(i=0; i < size; ++i){
            //kontrola zda na aktualne se posouvajicim policku neni hrac
            for(k=0; k < n; ++k){
                if(this->getPlayer(k)->getPosition() == QPoint(i,point.y()-1)){
                    switch(k){
                        case 0: p_0 = true; break;
                        case 1: p_1 = true; break;
                        case 2: p_2 = true; break;
                        case 3: p_3 = true; break;
                    }
                }
            }
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j += size;
        }

        this->updatePlayersV(p_0, p_1, p_2, p_3, 1);
    }
    //shift left
    else if(point.y() == size+1){
        j = point.x()*size - 1;
        for(i=0; i < size; ++i){
            //kontrola zda na aktualne se posouvajicim policku neni hrac
            for(k=0; k < n; ++k){
                if(this->getPlayer(k)->getPosition() == QPoint(point.x()-1,i)){
                    switch(k){
                        case 0: p_0 = true; break;
                        case 1: p_1 = true; break;
                        case 2: p_2 = true; break;
                        case 3: p_3 = true; break;
                    }
                }
            }
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j -= 1;
        }

        this->updatePlayersH(p_0, p_1, p_2, p_3, -1);
    }
    //shift right
    else if(point.y() == 0){
        j = (point.x()-1)*size;
        for(i=0; i < size; ++i){
            //kontrola zda na aktualne se posouvajicim policku neni hrac
            for(k=0; k < n; ++k){
                if(this->getPlayer(k)->getPosition() == QPoint(point.x()-1,i)){
                    switch(k){
                        case 0: p_0 = true; break;
                        case 1: p_1 = true; break;
                        case 2: p_2 = true; break;
                        case 3: p_3 = true; break;
                    }
                }
            }
            x = tiles[j];
            tiles[j] = newTile;
            newTile = x;
            j += 1;
        }

        this->updatePlayersH(p_0, p_1, p_2, p_3, 1);
    }
}

/**
 * @brief Board::updatePlayersV
 * @param p_0   player 0
 * @param p_1   player 1
 * @param p_2   player 2
 * @param p_3   player 3
 * @param add   direction
 *
 * Update player position during shifting - vertical shift
 */
void Board::updatePlayersV(bool p_0, bool p_1, bool p_2, bool p_3, int add){
    int size = static_cast<signed int>(this->size);
    Player* pl;
        if(p_0){    //player 1
            pl = this->getPlayer(0);
            if (pl->getPosition().x() == 0 && add == -1){
                pl->setPositionX(size-1);
            }
            else if (pl->getPosition().x() == size-1 && add == 1){
                pl->setPositionX(0);
            }
            else{
                pl->setPositionX(pl->getPosition().x()+add);
            }
        }
        if(p_1){    //player 2
            pl = this->getPlayer(1);
            if (pl->getPosition().x() == 0 && add == -1){
                pl->setPositionX(size-1);
            }
            else if (pl->getPosition().x() == size-1 && add == 1){
                pl->setPositionX(0);
            }
            else{
                pl->setPositionX(pl->getPosition().x()+add);
            }
        }
        if(p_2){    //player 3
            pl = this->getPlayer(2);
            if (pl->getPosition().x() == 0 && add == -1){
                pl->setPositionX(size-1);
            }
            else if (pl->getPosition().x() == size-1 && add == 1){
                pl->setPositionX(0);
            }
            else{
                pl->setPositionX(pl->getPosition().x()+add);
            }
        }
        if(p_3){    //player 4
            pl = this->getPlayer(3);
            if (pl->getPosition().x() == 0 && add == -1){
                pl->setPositionX(size-1);
            }
            else if (pl->getPosition().x() == size-1 && add == 1){
                pl->setPositionX(0);
            }
            else{
                pl->setPositionX(pl->getPosition().x()+add);
            }
        }
}

/**
 * @brief Board::updatePlayersH
 * @param p_0   player 0
 * @param p_1   player 1
 * @param p_2   player 2
 * @param p_3   player 3
 * @param add   direction
 *
 * Update player position during shifting - horizontal shift
 */
void Board::updatePlayersH(bool p_0, bool p_1, bool p_2, bool p_3, int add){
    int size = static_cast<signed int>(this->size);
    Player* pl;
        if(p_0){    //player 1
            pl = this->getPlayer(0);
            if (pl->getPosition().y() == 0 && add == -1){
                pl->setPositionY(size-1);
            }
            else if (pl->getPosition().y() == size-1 && add == 1){
                pl->setPositionY(0);
            }
            else{
                pl->setPositionY(pl->getPosition().y()+add);
            }
        }
        if(p_1){    //player 2
            pl = this->getPlayer(1);
            if (pl->getPosition().y() == 0 && add == -1){
                pl->setPositionY(size-1);
            }
            else if (pl->getPosition().y() == size-1 && add == 1){
                pl->setPositionY(0);
            }
            else{
                pl->setPositionY(pl->getPosition().y()+add);
            }
        }
        if(p_2){    //player 3
            pl = this->getPlayer(2);
            if (pl->getPosition().y() == 0 && add == -1){
                pl->setPositionY(size-1);
            }
            else if (pl->getPosition().y() == size-1 && add == 1){
                pl->setPositionY(0);
            }
            else{
                pl->setPositionY(pl->getPosition().y()+add);
            }
        }
        if(p_3){    //player 4
            pl = this->getPlayer(3);
            if (pl->getPosition().y() == 0 && add == -1){
                pl->setPositionY(size-1);
            }
            else if (pl->getPosition().y() == size-1 && add == 1){
                pl->setPositionY(0);
            }
            else{
                pl->setPositionY(pl->getPosition().y()+add);
            }
        }
}

/**
 * @brief Board::data
 * @return data
 *
 * Set game fingerprint
 */
QString Board::data()
{
    QString data = "";

    //ulozi kameny
    for (int i  = 0; i < this->tiles.count(); i++)
    {
        Tile *t = this->tiles[i];
        data.append(t->toCSV());
    }

    //ulozi venkovni sutry
    for (int i = 0; i < this->outter.count(); i++)
    {
        Tile *t = this->tiles[i];
        data.append("O" + t->toCSV());
    }

    //ulozi hrace
    for (int i = 0; i < this->players.count(); i++)
    {
        Player *p = this->players[i];
        data.append(p->toCSV());
    }

    //ulozi poklady
    data.append(this->treasures->toCSV(false));

    //ulozi karty
    data.append(this->cards->toCSV(true));

    data.append("B;");
    data.append(QString::number(this->b_type) + ";");
    data.append(QString::number(this->b_row) + ";");
    data.append(QString::number(this->b_col) + "\n");

    data.append("S;");
    data.append(QString::number(this->size) + "\n");

    data.append("A;");
    data.append(QString::number(this->act) + "\n");

    data.append("I" + this->newTile->toCSV());

    data.append("ST;");
    data.append(QString::number(this->state) + "\n");

    return data;
}

/**
 * @brief Board::load
 * @param filename      file load
 * @param cfgString     undo
 *
 * Load fingerprint from file/undo
 */
void Board::load(QString filename, QString cfgString = "")
{
    //nuluje vnitrni vektory
    //QVector<Tile*> tiles;
    //QVector<Tile*> outter;
    //QVector<Player*> players;
    //unsigned int size;
    //unsigned int act;
    //TreasurePack* treasures;
    //TreasurePack* cards;
    //QVector<Board> board;

    this->tiles.clear();
    this->outter.clear();
    this->players.clear();

    //treasures vectory nemuzu mazat, metoda jen pro nastaveni
    //vytvarim pomocne vektory
    QVector<Treasure *> ts;
    QVector<Treasure *> cs;

    QTextStream *in;
    QFile *file;

    if (cfgString.isEmpty())
    {
        file = new QFile(filename);
        file->open(QFile::ReadOnly | QFile::Text);
        in = new QTextStream(file);
    }
    else
    {
        in = new QTextStream(&cfgString);
    }

    while (!in->atEnd())
    {
        QString line;
        line = in->readLine();
        QStringList l = line.split(';');

        //parsovani radku

        if (l.size() == 2 && l[0] == "A")
        {
            this->act = l[1].toInt();
        }
        else if (l.size() == 2 && l[0] == "S")
        {
            this->size = l[1].toInt();
        }
        else if (l.size() == 4 && l[0] == "B")
        {
            this->b_type = l[1].toInt();
            this->b_row = l[2].toInt();
            this->b_col = l[3].toInt();
        }
        else if (l.size() == 2 && l[0] == "CP")
        {
            Treasure *t = new Treasure(l[1].toInt());
            cs.push_back(t);
        }
        else if (l.size() == 2 && l[0] == "P")
        {
            Treasure *t = new Treasure(l[1].toInt());
            ts.push_back(t);
        }
        else if (l.size() == 2 && l[0] == "ST")
        {
            this->state = l[1].toInt();
        }
        else if (l.size() == 7 && l[0] == "P")
        {
            QPoint pos;
            pos.setX(l[1].toInt());
            pos.setY(l[2].toInt());
            Player *p = new Player(l[4], pos);
            p->addPoints(l[3].toInt());
            Treasure *t = new Treasure(l[6].toInt());
            p->setCard(t);
            this->players.push_back(p);

        }
        else if (l.size() == 3 && l[0] == "OT")
        {
            int move = l[1].toInt();
            if (move == 1010 || move == 101)
            {
                Tile *tile = new TileOutter(l[2].toInt());
                this->outter.push_back(tile);
            }
            else if (move == 1100 || move == 110 || move == 11 || move == 1001)
            {
                Tile *tile = new TileOutter(l[2].toInt());
                this->outter.push_back(tile);
            }
            else
            {
                Tile *tile = new TileOutter(l[2].toInt());
                this->outter.push_back(tile);
            }
        }
        else if (l.size() == 5 && l[0] == "OT")
        {
            int move = l[1].toInt();
            if (move == 1010 || move == 101)
            {
                Tile *tile = new TileOutter(l[2].toInt());
                this->outter.push_back(tile);
            }
            else if (move == 1100 || move == 110 || move == 11 || move == 1001)
            {
                Tile *tile = new TileOutter(l[2].toInt());
                this->outter.push_back(tile);
            }
            else
            {
                Tile *tile = new TileOutter(l[2].toInt());
                this->outter.push_back(tile);
            }

            //tu poklad neni, netreba resit
        }
        else if (l.size() == 3 && l[0] == "T")
        {
            int move = l[1].toInt();
            if (move == 1010 || move == 101)
            {
                Tile *tile = new TileStraight(l[2].toInt());
                this->tiles.push_back(tile);
            }
            else if (move == 1100 || move == 110 || move == 11 || move == 1001)
            {
                Tile *tile = new TileCorner(l[2].toInt());
                this->tiles.push_back(tile);
            }
            else
            {
                Tile *tile = new TileCross(l[2].toInt());
                this->tiles.push_back(tile);
            }
        }
        else if (l.size() == 5 && l[0] == "T")
        {
            int move = l[1].toInt();
            Tile *tile;
            if (move == 1010 || move == 101)
            {
                tile = new TileStraight(l[2].toInt());
            }
            else if (move == 1100 || move == 110 || move == 11 || move == 1001)
            {
                tile = new TileCorner(l[2].toInt());

            }
            else
            {
                tile = new TileCross(l[2].toInt());
            }

            //poklad na kameni

            Treasure *t = new Treasure(l[4].toInt());
            tile->setTreasure(t);
            this->tiles.push_back(tile);
        }
        else if (l.size() == 3 && l[0] == "IT")
        {
            int move = l[1].toInt();
            if (move == 1010 || move == 101)
            {
                Tile *tile = new TileStraight(l[2].toInt());
                this->newTile = tile;
            }
            else if (move == 1100 || move == 110 || move == 11 || move == 1001)
            {
                Tile *tile = new TileCorner(l[2].toInt());
                this->newTile = tile;
            }
            else
            {
                Tile *tile = new TileCross(l[2].toInt());
                this->newTile = tile;;
            }
        }
        else if (l.size() == 5 && l[0] == "T")
        {
            int move = l[1].toInt();
            Tile *tile;
            if (move == 1010 || move == 101)
            {
                tile = new TileStraight(l[2].toInt());
            }
            else if (move == 1100 || move == 110 || move == 11 || move == 1001)
            {
                tile = new TileCorner(l[2].toInt());

            }
            else
            {
                tile = new TileCross(l[2].toInt());
            }

            //poklad na kameni

            Treasure *t = new Treasure(l[4].toInt());
            tile->setTreasure(t);
            this->newTile = tile;
        }
    }

    if (cfgString.isEmpty())    //uzavreni souboru
    {
        file->close();
    }
}

/**
 * @brief Board::makeBckp
 *
 * Save fingerprint for possible undo
 */
void Board::makeBckp()
{
    this->bckpList.push_back(this->data());
}

/**
 * @brief Board::undo
 *
 * Operation undo while playing
 */
void Board::undo()
{
    if (this->bckpList.isEmpty()) return;

    this->load("", this->bckpList.last());
    this->bckpList.pop_back();
}
