//ICP-Labyrinth 2014/2015
/**
 * @file       mainwindow.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Implementation of functions for show main application window (menu and game).
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QFile>

const unsigned int IMG_SIZE = 44;   //!< image size */
const unsigned int E_SIZE = 50;     //!< size of space outter main board */

/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * Contructor of main window
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //qsrand(qrand()); //pro testovani
    qsrand(QTime::currentTime().msec());    //random

    ui->setupUi(this);

    this->size = 7;
    this->quantity = 12;

    //GUI objekty
    scene = new QGraphicsScene(this);
    newTile = new QGraphicsScene(this);
    card = new QGraphicsScene(this);

    btn_rotate = new QPushButton("Rotate", this);
    btn_addPlayer = new QPushButton("Add Player", this);

    l_addPlayers = new QLabel(this);
    l_players = new QLabel("Players:", this);
    l_sizeView = new QLabel("Choosen size: " + QString::number(this->size), this);
    l_quantityView = new QLabel("Choosen quantity: " + QString::number(this->quantity), this);

    l_size = new QLabel("Size:", this);
    l_quantity = new QLabel("Quantity:", this);
    l_state = new QLabel(this);
    l_player_res  = new QLabel(this);

    gw_board = new QGraphicsView(this);
    gw_newTile = new QGraphicsView(this);
    gw_card = new QGraphicsView(this);
    le_player = new QLineEdit(this);

    btn_quantity_12 = new QPushButton("12", this);
    btn_quantity_24 = new QPushButton("24", this);
    btn_size_5 = new QPushButton("5", this);
    btn_size_7 = new QPushButton("7", this);
    btn_size_9 = new QPushButton("9", this);
    btn_size_11 = new QPushButton("11", this);

    btn_save = new QPushButton("Save", this);
    btn_load = new QPushButton("Load", this);
    btn_undo = new QPushButton("Undo", this);

    btn_play = new QPushButton("Play!", this);

    board = new Board();

    //zadne scroll bary
    gw_board->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_board->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_newTile->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_newTile->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_card->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_card->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

/**
 * @brief MainWindow::menu
 *
 * Start and show menu
 */
void MainWindow::menu(){
    //skryt objekty hry
    this->hideGame();

    //nastavit pozice
    l_addPlayers->setGeometry(QRect(250, 40, 90, 80));
    l_sizeView->setGeometry(QRect(20, 100, 110, 20));
    l_quantityView->setGeometry(QRect(380, 100, 150, 20));
    le_player->setGeometry(QRect(150, 20, 80, 20));
    le_player->setMaxLength(10);

    l_size->setGeometry(QRect(20, 20, 80, 20));
    l_quantity->setGeometry(QRect(380, 20, 115, 20));
    l_player_res->setGeometry(QRect(20, 160, 280, 20));
    l_players->setGeometry(QRect(250, 20, 80, 20));

    btn_quantity_12->setGeometry(QRect(380, 40, 25, 25));
    btn_quantity_24->setGeometry(QRect(405, 40, 25, 25));
    btn_size_5->setGeometry(QRect(20, 40, 25, 25));
    btn_size_7->setGeometry(QRect(45, 40, 25, 25));
    btn_size_9->setGeometry(QRect(70, 40, 25, 25));
    btn_size_11->setGeometry(QRect(95, 40, 25, 25));

    btn_play->setGeometry(QRect(340, 140, 75, 40));

    btn_addPlayer->setGeometry(QRect(150, 50, 85, 23));      //tlacitko pridat hrace
    setFixedSize(540, 200);                       //cele okno

    //connections
    connect(btn_quantity_12, SIGNAL (released()), this, SLOT (handle_btn_quantity_12()));
    connect(btn_quantity_24, SIGNAL (released()), this, SLOT (handle_btn_quantity_24()));
    connect(btn_size_5, SIGNAL (released()), this, SLOT (handle_btn_size_5()));
    connect(btn_size_7, SIGNAL (released()), this, SLOT (handle_btn_size_7()));
    connect(btn_size_9, SIGNAL (released()), this, SLOT (handle_btn_size_9()));
    connect(btn_size_11, SIGNAL (released()), this, SLOT (handle_btn_size_11()));
    connect(btn_addPlayer, SIGNAL (released()), this, SLOT (handle_btn_addPlayer()));
    connect(btn_play, SIGNAL (released()), this, SLOT (handle_btn_play()));
}

/**
 * @brief MainWindow::hideMenu
 *
 * Hide objects of menu
 */
void MainWindow::hideMenu(){
    btn_addPlayer->hide();
    l_sizeView->hide();
    l_quantityView->hide();
    //l_size->hide();
    //l_quantity->hide();
    le_player->hide();
    btn_quantity_12->hide();
    btn_quantity_24->hide();
    btn_size_5->hide();
    btn_size_7->hide();
    btn_size_9->hide();
    btn_size_11->hide();
    btn_play->hide();
}

/**
 * @brief MainWindow::game
 *
 * Start and show game
 */
void MainWindow::game(){
    //skryt menu
    this->hideMenu();
    //zobrazit hru
    this->showGame();

    this->board->setBoard(this->size);   //vygenerovat kameny pro hraci desku
    this->board->setOutterFields(this->size);   //vygenerování policek pro vsunuti kamene
    this->board->setTreasures(this->quantity);   //vygenerovat poklady
    this->board->setCards(this->quantity);   //vygenerovat karty

    this->board->getCards()->shuffle();     //zamicha karty
    this->board->getTreasures()->shuffle(); //zamicha poklady

    this->board->setTreasureToTile(this->size, this->quantity);   //prirazeni kamenum poklad
    this->board->setCardToPlayers();         //prirazeni karty hraci

    gw_board->setInteractive(true);

    board->setNewTile();          //vygenerovani noveho kamenu mimo desku

    this->board->state = Board::SHIFT;

    gw_board->setCursor(Qt::PointingHandCursor);

    this->load();

    //connections
    connect(btn_rotate, SIGNAL (released()), this, SLOT (handle_btn_rotate()));
    connect(btn_save, SIGNAL (released()), this, SLOT (handle_btn_save()));
    connect(btn_load, SIGNAL (released()), this, SLOT (handle_btn_load()));
    connect(btn_undo, SIGNAL (released()), this, SLOT (handle_btn_undo()));
}

/**
 * @brief MainWindow::load
 *
 * Load object for game after menu or file load
 */
void MainWindow::load(){

    this->scene->clear();

    this->genBoard();   //generovani hraciho pole

    this->width = this->size*IMG_SIZE+100;    //sirka sceny
    this->height = this->size*IMG_SIZE+100;   //vyska sceny

    this->drawCard(this->board->getActPlayer());

    l_quantity->clear();

    l_quantity->setAlignment(Qt::AlignCenter);
    l_state->setAlignment(Qt::AlignCenter);
    l_player_res->setAlignment(Qt::AlignCenter);
    l_player_res->setText(this->board->getActPlayer()->getName());

    //nastaveni zobrazovani objektu
    gw_board->setGeometry(QRect(10, 10, width+2, height+2));    //prizpusobeni okna hraci desky
    btn_rotate->setGeometry(QRect(60, height+30, 70, 23));      //tlacitko rotace
    btn_save->setGeometry(QRect(width+30, 10, 60, 23));      //tlacitko save
    btn_load->setGeometry(QRect(width+30, 40, 60, 23));      //tlacitko load
    btn_undo->setGeometry(QRect(width+30, 200, 60, 35));      //tlacitko undo
    l_players->setGeometry(QRect(185, height+15, 80, 60));      //stitek hraci
    l_addPlayers->setGeometry(QRect(250, height+15, 90, 70));   //stitek seznam hracu
    l_size->setGeometry(QRect(360, height+15, 80, 70));         //stitek barev hracu
    l_state->setGeometry(QRect(width+20, 100, 80, 20));         //stitek akce
    l_quantity->setGeometry(QRect(width+20, height-100, 70, 60));  //stitek vitezneho hrace
    l_player_res->setGeometry(QRect(width+20, 80, 80, 20));          //aktualni hrac
    gw_newTile->setGeometry(QRect(10, height+20, 44, 44));      //novy kamen mimo hraci desku
    gw_card->setGeometry(QRect(width+35, 120, 44, 44));      //karta
    setFixedSize(10+width+20+70, 10+height+25+50);                       //cele okno

    switch(this->board->getNumPlayers()){
        case 1: l_size->setText("red"); break;
        case 2: l_size->setText("red\nblue"); break;
        case 3: l_size->setText("red\nblue\ngreen"); break;
        case 4: l_size->setText("red\nblue\ngreen\ngrey"); break;
    }

    this->drawState();      //zobrazi stav

    this->drawNewTile();        //zobrazi novy kamen

    gw_board->setScene(this->scene);  //zobrazi board
}

/**
 * @brief MainWindow::hideGame
 *
 * Hide objects of game
 */
void MainWindow::hideGame(){

    btn_rotate->hide();
    gw_board->hide();
    gw_newTile->hide();
    gw_card->hide();
    btn_save->hide();
    btn_load->hide();
    btn_undo->hide();
    l_state->hide();
}

/**
 * @brief MainWindow::showGame
 *
 * Show objects of game
 */
void MainWindow::showGame(){

    btn_rotate->show();
    gw_board->show();
    gw_newTile->show();
    gw_card->show();
    btn_save->show();
    btn_load->show();
    btn_undo->show();
    l_state->show();
}

/**
 * @brief MainWindow::~MainWindow
 *
 * Implicit destructor
 */
MainWindow::~MainWindow()
{
    //delete this->board->getCards();
    delete this->board->getTreasures();

    delete scene;
    delete newTile;
    delete card;

    delete btn_rotate;
    delete btn_addPlayer;

    delete l_addPlayers;
    delete l_players;
    delete l_sizeView;
    delete l_quantityView;

    delete l_size;
    delete l_quantity;
    delete l_state;
    delete l_player_res;
    delete le_player;

    delete btn_quantity_12;
    delete btn_quantity_24;
    delete btn_size_5;
    delete btn_size_7;
    delete btn_size_9;
    delete btn_size_11;
    delete btn_save;
    delete btn_load;
    delete btn_undo;
    delete btn_play;

    delete gw_board;
    delete gw_newTile;
    delete gw_card;

    delete board;

    delete ui;
}

/**
 * @brief MainWindow::mousePressEvent
 * @param event
 *
 * Event for left mouse click on board
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(this->board->state == Board::STAY){
        event->ignore();
    }
    event->accept();

    if (event->button() == Qt::LeftButton){
        if(event->x() < 10 || event->y() < 10){return;}
        unsigned int posX = event->x()-10;
        unsigned int posY = event->y()-10;

        unsigned int width = this->gw_board->width();
        unsigned int height = this->gw_board->height();

        if((posX > 0 && posX < width) && (posY > 0 && posY < height)){

            if ((posX > width - 50 || posX < 50) || (posY > height - 50 || posY < 50))
            {
                //mimo hraci plochu
              if (this->board->state == Board::SHIFT){

                if ((posX > width - IMG_SIZE || posX < IMG_SIZE) || (posY > height - IMG_SIZE || posY < IMG_SIZE))
                {

                    //mimo hraci plochu na urovni nasouvacich policek

                    if ((posX <= E_SIZE && ((posY <= E_SIZE) || (posY >= height - E_SIZE))))
                        return;     //kraje
                    if ((posY <= E_SIZE && ((posX <= E_SIZE) || (posX >= width - E_SIZE))))
                        return;     //kraje
                    if ((posX >= width - E_SIZE && ((posY <= E_SIZE) || (posY >= height - E_SIZE))))
                        return;     //kraje
                    if ((posY >= height - E_SIZE && ((posX <= E_SIZE) || (posX >= width - E_SIZE))))
                        return;     //kraje

                    if (posX > 50){ posX -= 2*(E_SIZE-IMG_SIZE); }
                    if (posY > 50){ posY -= 2*(E_SIZE-IMG_SIZE); }
                    unsigned int row = (posY) / IMG_SIZE;
                    unsigned int col = (posX) / IMG_SIZE;

                    if ( (this->board->getB_type() == 1 && this->board->getB_col() == col && this->board->getB_row() != row) ||
                         (this->board->getB_type() == 2 && this->board->getB_col() != col && this->board->getB_row() == row) ){   //nevraceni zpet v nasledujich tahu
                        return;
                    }
                        if (row % 2 == 0 && col % 2 == 0)
                        {
                            this->board->makeBckp();
                            board->insertNewTile(QPoint(row, col));
                            this->genBoard();
                            this->drawNewTile();
                            this->board->state = Board::MOVE;
                            this->drawState();

                            this->board->setB_row(row);
                            this->board->setB_col(col);
                            this->board->setB_type((row == 0 || row == (this->size+1)) ? 1 : 2);
                        }                    
                 }
              }
            }
            else
            {
                if (this->board->state == Board::MOVE){

                    this->board->makeBckp();

                    unsigned int row = (posY - 50) / IMG_SIZE;
                    unsigned int col = (posX - 50) / IMG_SIZE;

                    Player* p = this->board->getActPlayer();

                    if (this->board->canMove(p->getPosition().x() * this->size + p->getPosition().y(), row * this->size + col)){
                        p->setPosition(QPoint(row,col));


                        this->board->state = Board::SHIFT;
                        this->drawState();

                        Tile *t = this->board->getTile(row * this->size + col);
                        if(t->getTreasure() != NULL && p->getCard()->getCode() == t->getTreasure()->getCode()){
                            p->addPoints(1);

                            if(p->getPoints() >= this->quantity / this->board->getNumPlayers()){//quantity / pocet hracu
                                this->board->state = Board::STAY;
                                QString str = p->getName() + "\nwon!";
                                l_quantity->setText(str);
                            }

                            p->setCard(this->board->getCards()->getTreasure());
                            this->board->getCards()->removeTreasure();

                            t->setTreasure(NULL);
                        }

                        this->board->actPlus();
                        l_player_res->setText(this->board->getActPlayer()->getName());
                        this->drawCard(this->board->getActPlayer());
                    }

                    this->genBoard();
                }
            }
        }
    }
}

/**
 * @brief MainWindow::handle_btn_rotate
 *
 * Handle button rotate
 */
void MainWindow::handle_btn_rotate()
{
    this->board->getNewTile()->rotate();   //otoceni

    //zavola prekresleni
    this->drawNewTile();
}

/**
 * @brief MainWindow::handle_btn_addPlayer
 *
 * Handle button add player
 */
void MainWindow::handle_btn_addPlayer()
{
    unsigned int i, n;
    n = this->board->getNumPlayers();
    if (n >= 4){
       l_player_res->setText("MAX 4 Players");
    }
    else{
        if (le_player->text().isEmpty()){
            this->board->addPlayer(new Player());
        }
        else{
            for (i=0; i < n; ++i ){
                if(!(le_player->text().compare(board->getPlayer(i)->getName()))){
                    l_player_res->setText("Name already exists");
                    break;
                }
            }
            if(i == board->getNumPlayers()){
                this->board->addPlayer(new Player(le_player->text()));
                le_player->clear();
            }
        }

        //zavola prekresleni
        this->drawPlayers();
    }
}

/**
 * @brief MainWindow::drawNewTile
 *
 * Set new tile visible
 */
void MainWindow::drawNewTile()
{
    QPixmap obr;
    obr.load(this->getTileImage(this->board->getNewTile()));
    this->newTile->addPixmap(obr);        //prida obrazek do okenka
    if(board->getNewTile()->getTreasure() != NULL){
        obr.load(this->getTreasureImage(this->board->getNewTile()));
        this->newTile->addPixmap(obr);     //ziska obrazek
    }
    gw_newTile->setScene(newTile);  //zobrazi novy kamen
}

/**
 * @brief MainWindow::drawCard
 *
 * Set card visible
 */
void MainWindow::drawCard(Player* p)
{
    QPixmap pix(":/images/E.png");
    this->card->addPixmap(pix);

    QPixmap obr;
    obr.load(":/images/treasure/T-" + QString::number(p->getCard()->getCode()) + ".png");

    this->card->addPixmap(obr);

    gw_card->setScene(card);
}

/**
 * @brief MainWindow::drawPlayers
 *
 * Set players name visible
 */
void MainWindow::drawPlayers()
{
    QString str;
    unsigned int i, n = board->getNumPlayers();
    for (i=0; i<n; ++i){
        str += board->getPlayer(i)->getName() + "\n";
    }
    str.remove(str.length()-1,1);   //odstraneni posledniho znaku
    l_addPlayers->setText(str);
    l_addPlayers->repaint();
}

/**
 * @brief MainWindow::handle_btn_size_5
 *
 * Handle button size 5
 */
void MainWindow::handle_btn_size_5()
{
    this->size = 5;
    this->drawSize();
}

/**
 * @brief MainWindow::handle_btn_size_7
 *
 * Handle button size 7
 */
void MainWindow::handle_btn_size_7()
{
    this->size = 7;
    this->drawSize();
}

/**
 * @brief MainWindow::handle_btn_size_9
 *
 * Handle button size 9
 */
void MainWindow::handle_btn_size_9()
{
    this->size = 9;
    this->drawSize();
}

/**
 * @brief MainWindow::handle_btn_size_11
 *
 * Handle button size 11
 */
void MainWindow::handle_btn_size_11()
{
    this->size = 11;
    this->drawSize();
}

/**
 * @brief MainWindow::drawSize
 *
 * Set size visible
 */
void MainWindow::drawSize(){
    QString str;
    str = "Choosen size: " + QString::number(this->size);
    l_sizeView->setText(str);
    l_sizeView->repaint();
}

/**
 * @brief MainWindow::drawState
 *
 * Set state
 */
void MainWindow::drawState(){
    switch(this->board->state){
        case Board::MOVE: l_state->setText("MOVE"); break;
        case Board::SHIFT: l_state->setText("SHIFT"); break;
    default: l_state->clear();
    }
}

/**
 * @brief MainWindow::handle_btn_quantity_12
 *
 * Handle button quantity 12
 */
void MainWindow::handle_btn_quantity_12()
{
    this->quantity = 12;
    this->drawQuantity();
}

/**
 * @brief MainWindow::handle_btn_quantity_24
 *
 * Handle button quantity 24
 */
void MainWindow::handle_btn_quantity_24()
{
    this->quantity = 24;
    this->drawQuantity();
}

/**
 * @brief MainWindow::drawQuantity
 *
 * Set quantity visible
 */
void MainWindow::drawQuantity(){
    QString str;
    str = "Choosen quantity: " + QString::number(this->quantity);
    l_quantityView->setText(str);
    l_quantityView->repaint();
}

/**
 * @brief MainWindow::handle_btn_play
 *
 * Handle button play
 */
void MainWindow::handle_btn_play()
{
    if(board->getNumPlayers() >= 2){
        this->board->setSize(this->size);
        this->board->setPlayerPos();
        this->game();
    }
    else{
        l_player_res->setText("Restriction: 2-4 players needed for game");
    }
}

/**
 * @brief MainWindow::handle_btn_save
 *
 * Handle button save
 */
void MainWindow::handle_btn_save()
{
    //zapise do souboru csv data
    //qDebug(board->data().toStdString().c_str());

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"),
    "",
    tr("Files (*.*)"));

    if(fileName.isEmpty()){return;}

    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Text);

    QTextStream out(&file);
    out << board->data();

    file.flush();
    file.close();
}

/**
 * @brief MainWindow::handle_btn_load
 *
 * Handle button load
 */
void MainWindow::handle_btn_load()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
    "",
    tr("Files (*.*)"));

    if(fileName.isEmpty()){return;}

    board->load(fileName, "");

    this->size = this->board->getSize();

    this->drawPlayers();

    this->load();
}

/**
 * @brief MainWindow::handle_btn_undo
 *
 * Undo current operation
 */
void MainWindow::handle_btn_undo()
{
    this->board->undo();

    this->load();
}

/**
 * @brief MainWindow::genBoard
 *
 * Generate board
 */
void MainWindow::genBoard(){

    Tile * tile;
    unsigned int i, j, l;
    int x = 0, y = 0, k = 0, a, b;
    QPixmap obr;
    QGraphicsPixmapItem *pixmapItem;

    /* Generovani kamenu hraci desky */
    for (i=0; i < this->size; ++i){
        for (j=0; j < this->size; ++j){
            //pozice moznych vstupu kamenu
            if(((i==0 || i==(this->size-1)) && j%2==1) || ((j==0 || j==(this->size-1)) && i%2==1)){
                tile = board->getOutterField(k);
                k++;
                obr.load(this->getTileImage(tile));
                pixmapItem = scene->addPixmap(obr);
                a=x;
                b=y;
                if(i==0){a=x+50;}
                else if(i==(this->size-1)){a=x+50;b=y+100;}
                if(j==0){b=y+50;}
                else if(j==(this->size-1)){b=y+50;a=x+100;}
                pixmapItem->setX(a);
                pixmapItem->setY(b);
            }
            int souradnice = j+i*this->size;
            tile = board->getTile(souradnice);    //odkaz na kamen

            //vykresleni kamenu

            obr.load(this->getTileImage(tile));     //ziska obrazek

            pixmapItem = scene->addPixmap(obr); //prida obrazek do sceny a vrati odkaz na nej

            pixmapItem->setX(x+50);
            pixmapItem->setY(y+50);

            //vykresleni pokladu
            if(tile->getTreasure() != NULL){
                obr.load(this->getTreasureImage(tile));     //ziska obrazek

                pixmapItem = scene->addPixmap(obr); //prida obrazek do sceny a vrati odkaz na nej

                pixmapItem->setX(x+50);
                pixmapItem->setY(y+50);
            }

            //vykresleni hracu
            for (l=0; l < board->getNumPlayers(); ++l){
                Player* p;
                p = board->getPlayer(l);
                if (i == static_cast<unsigned int>(p->getPosition().x()) && j == static_cast<unsigned int>(p->getPosition().y())){
                    obr.load(this->getPlayerImage(l));     //ziska obrazek
                    pixmapItem = scene->addPixmap(obr); //prida obrazek do sceny a vrati odkaz na nej

                    pixmapItem->setX(x+50);
                    pixmapItem->setY(y+50);
                }
            }

            x += IMG_SIZE; //posunuti v ose X
        }
        /* Odradkovani */
        x = 0;
        y += IMG_SIZE;  //posunuti v ose Y
    }
}

/**
 * @brief MainWindow::getTileImage
 * @param tile
 * @return str
 *
 * Get tile image path
 */
QString MainWindow::getTileImage(Tile* tile)
{
    unsigned int move = tile->getMove().getMove();
    unsigned int rot = tile->getRotation();
    QString str = ":/images/C.png";

    if (move == 1010 || move == 101){
        switch(rot){
            case 1: str = ":/images/S-1.png"; break;
            case 2: str = ":/images/S-2.png"; break;
        }
    }
    else if (move == 1100 || move == 110 || move == 11 || move == 1001){
        switch(rot){
            case 1: str = ":/images/L-1.png"; break;
            case 2: str = ":/images/L-2.png"; break;
            case 3: str = ":/images/L-3.png"; break;
            case 4: str = ":/images/L-4.png"; break;
        }
    }
    else if(move == 1110 || move == 111 || move == 1011 || move == 1101){
        switch(rot){
            case 1: str = ":/images/T-1.png"; break;
            case 2: str = ":/images/T-2.png"; break;
            case 3: str = ":/images/T-3.png"; break;
            case 4: str = ":/images/T-4.png"; break;
        }
    }
    else{
       str = ":/images/E.png";
    }

    return str;
}

/**
 * @brief MainWindow::getTreasureImage
 * @param tile
 * @return str
 *
 * Get treasure image path
 */
QString MainWindow::getTreasureImage(Tile* tile)
{
    QString str = ":/images/treasure/T-" + QString::number(tile->getTreasure()->getCode()) + ".png";
    return str;
}

/**
 * @brief MainWindow::getPlayerImage
 * @param i
 * @return str
 *
 * Get player image path
 */
QString MainWindow::getPlayerImage(int i)
{
    QString str = ":/images/C.png";

    switch(i){
        case 0: str = ":/images/P-1.png"; break;
        case 1: str = ":/images/P-2.png"; break;
        case 2: str = ":/images/P-3.png"; break;
        case 3: str = ":/images/P-4.png"; break;
    }

    return str;
}
