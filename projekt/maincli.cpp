//ICP-Labyrinth 2014/2015
/**
* @file       maincli.cpp
* @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
* @date       May 2015
*
* Implementation of functions for show main CLI window (demonstration of game).
*/

#include "maincli.h"

QTextStream streamIn(stdin);

/**
 * @brief MainCLI::MainCLI
 *
 * Constructor of main CLI window
 */
MainCLI::MainCLI(){
    qsrand(QTime::currentTime().msec());    //random

    board = new Board();
}

/**
 * @brief MainCLI::~MainCLI
 *
 * Implicit destructor
 */
MainCLI::~MainCLI(){
    delete board;
}

/**
 * @brief MainCLI::help
 *
 * Print bief info
 */
void MainCLI::help(){
    QTextStream(stdout) << "INFO\n";
    QTextStream(stdout) << "This program was written to demonstrate separation function part from GUI.\n";
    QTextStream(stdout) << "You can try shift (insert new tile and rotate it) and move players.\n";
    QTextStream(stdout) << "In this demostration there is a board 7x7 size and two players.\n";
    QTextStream(stdout) << "\nPress any key to continue.\n";

    streamIn.readLine();
}

/**
 * @brief MainCLI::getTileImage
 * @param tile
 * @return str
 *
 * Get Tile ASCII representation
 */
QString MainCLI::getTileImage(Tile* tile)
{
    unsigned int move = tile->getMove().getMove();
    unsigned int rot = tile->getRotation();
    QString str = "OOOOOOOOO";

    if (move == 1010 || move == 101){
        switch(rot){
        case 1: str = "###   ###"; break;
        case 2: str = "# ## ## #"; break;
    }
    }
    else if (move == 1100 || move == 110 || move == 11 || move == 1001){
        switch(rot){
            case 1: str = "# ##  ###"; break;
            case 2: str = "# #  ####"; break;
            case 3: str = "###  ## #"; break;
            case 4: str = "####  # #"; break;
        }
    }
    else if(move == 1110 || move == 111 || move == 1011 || move == 1101){
        switch(rot){
            case 1: str = "# #   ###"; break;
            case 2: str = "# #  ## #"; break;
            case 3: str = "###   # #"; break;
            case 4: str = "# ##  # #"; break;
            }
    }
    else{
       str = "         ";
    }

    return str;
}

/**
 * @brief MainCLI::getPlayerImage
 * @param i
 * @return str
 *
 * Get Player ASCII representation
 */
QString MainCLI::getPlayerImage(int i)
{
    QString str = "O";

    switch(i){
        case 0: str = "a"; break;
        case 1: str = "i"; break;
        case 2: str = "n"; break;
        case 3: str = "s"; break;
    }

    return str;
}

/**
 * @brief MainCLI::genBoard
 *
 * Generate main board
 */
void MainCLI::genBoard(){
    Tile * tile;
    QString str;
    unsigned int i, j, l, u, v;

    QTextStream(stdout) << "\n";

    for (i=0; i < board->getSize(); ++i){
        str.clear();
        for (j=0; j < board->getSize(); ++j){
            int souradnice = j+i*board->getSize();
            tile = board->getTile(souradnice);    //odkaz na kamen
            str.append(getTileImage(tile));

            //vykresleni hracu
            for (l=0; l < board->getNumPlayers(); ++l){
                Player* p;
                p = board->getPlayer(l);
                if (i == static_cast<unsigned int>(p->getPosition().x()) && j == static_cast<unsigned int>(p->getPosition().y())){
                    str.insert(3+(j*9)+1,getPlayerImage(l));
                    str.remove(3+(j*9)+2,1);
                }
            }

        }

        for (u=0; u < 3; ++u){
            for (v=0; v < 8*board->getSize(); v+=7){
                QTextStream(stdout) << str[v+(u*3)];
                QTextStream(stdout) << str[++v+(u*3)];
                QTextStream(stdout) << str[++v+(u*3)];
            }
            QTextStream(stdout) << "\n";
        }
    }

    v=0;
    str.clear();
    str.append(this->getTileImage(this->board->getNewTile()));
    QTextStream(stdout) << "\n";
    QTextStream(stdout) << str[v] << str[v+1] << str[v+2] << "\n";
    QTextStream(stdout) << str[v+3] << str[v+4] << str[v+5] << "\n";
    QTextStream(stdout) << str[v+6] << str[v+7] << str[v+8] << "\n";
}

/**
 * @brief MainCLI::game
 *
 * Start game
 */
void MainCLI::game(){
    int size = 7;

    board->setSize(size);

    board->setBoard(board->getSize());   //vygenerovat kameny pro hraci desku
    board->setOutterFields(board->getSize());   //vygenerování policek pro vsunuti kamene

    board->setNewTile();          //vygenerovani noveho kamenu mimo desku

    board->state = Board::SHIFT;

    board->addPlayer(new Player());     //Player0
    board->addPlayer(new Player());     //Player1

    board->setPlayerPos();
    board->setNewTile();        //zobrazi novy kamen

    genBoard();   //generovani hraciho pole
}

/**
 * @brief MainCLI::shift
 * @param row
 * @param col
 * @return TRUE     seccessfully shifted
 * @return FALSE    invalid row or col
 *
 * Shift row or col
 */
bool MainCLI::shift(unsigned int row, unsigned int col){

    if (!(((row == 1 || row == board->getSize()) && col%2 == 0) || (row%2 == 0 && (col == 1 || col == board->getSize())))){
        return false;
    }

    if(row == 1){row=0;}
    if(col == 1){col=0;}
    if(row == board->getSize()){row=board->getSize()+1;}
    if(col == board->getSize()){col=board->getSize()+1;}

    if ( (this->board->getB_type() == 1 && this->board->getB_col() == col && this->board->getB_row() != row) ||
         (this->board->getB_type() == 2 && this->board->getB_col() != col && this->board->getB_row() == row) ){   //nevraceni zpet v nasledujich tahu
        return false;
    }

    board->insertNewTile(QPoint(row, col));

    this->board->setB_row(row);
    this->board->setB_col(col);
    this->board->setB_type((row == 0 || row == (this->board->getSize()+1)) ? 1 : 2);

    return true;
}

/**
 * @brief MainCLI::u_getShift
 *
 * Handle of shift
 */
void MainCLI::u_getShift(){
    QString str;
    QPoint point;
    QString s;
    bool konec = false;

    QTextStream(stdout) << "\n" << board->getActPlayer()->getName() << "\t"
                        << getPlayerImage(board->getActPlayer()->getName().right(1).toInt()-1) << "\n";

    do{
        konec = true;
        QTextStream(stdout) << "ROTATE (Y): ";

        s = streamIn.readLine();
        if(s == "Y" || s == "y"){
            this->board->getNewTile()->rotate();   //otoceni
            konec = false;
            genBoard();   //generovani hraciho pole
        }

    } while(!konec);

    do{
        QTextStream(stdout) << "SHIFT (1x2 1x4 1x6 7x2 7x4 7x6 and reversed)\nx: ";

        str = streamIn.readLine();

        point.setX(str.toInt());

        QTextStream(stdout) << "y: ";

        str = streamIn.readLine();

        point.setY(str.toInt());

        konec = this->shift(point.x(),point.y());

        if(!konec){QTextStream(stdout) << "---Invalid shift\n";}
    } while(!konec);

    genBoard();   //generovani hraciho pole
}

/**
 * @brief MainCLI::move
 * @param row
 * @param col
 * @return TRUE     seccessfully moved
 * @return FALSE    path not found
 *
 * Player move
 */
bool MainCLI::move(unsigned int row, unsigned int col){
    Player *p;
    p = board->getActPlayer();

    --row;
    --col;

    if (this->board->canMove(p->getPosition().x() * board->getSize() + p->getPosition().y(), row * board->getSize() + col)){
      p->setPosition(QPoint(row,col));
      this->board->actPlus();
      return true;
    }

    return false;
}

/**
 * @brief MainCLI::u_getMove
 *
 * Handle of move
 */
void MainCLI::u_getMove(){
    QString str;
    QPoint point;
    bool konec = false;

    QTextStream(stdout) << "\n" << board->getActPlayer()->getName() << "\t"
                        << getPlayerImage(board->getActPlayer()->getName().right(1).toInt()-1) << "\n";

    do{
        QTextStream(stdout) << "MOVE (1x1 - 7x7)\nx: ";

        str = streamIn.readLine();

        point.setX(str.toInt());

        QTextStream(stdout) << "y: ";

        str = streamIn.readLine();

        point.setY(str.toInt());

        konec = this->move(point.x(),point.y());

        if(!konec){QTextStream(stdout) << "---Invalid move\n";}
    } while(!konec);

    genBoard();   //generovani hraciho pole
}
