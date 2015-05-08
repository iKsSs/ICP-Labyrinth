#include "mainwindow.h"
#include "ui_mainwindow.h"

const unsigned int IMG_SIZE = 44;
const unsigned int E_SIZE = 50;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(qrand()); //pro testovani
    //qsrand(QTime::currentTime().msec());    //random

    ui->setupUi(this);

    this->size = 7;
    this->numPlayers = 0;
    this->quantity = 12;

    //GUI objekty
    scene = new QGraphicsScene(this);
    newTile = new QGraphicsScene(this);

    btn_rotate = new QPushButton("Rotate", this);
    btn_addPlayer = new QPushButton("Add Player", this);

    l_addPlayers = new QLabel(this);
    l_players = new QLabel("Players:", this);
    l_sizeView = new QLabel("Choosen size: " + QString::number(this->size), this);

    l_size = new QLabel("Choose size:", this);

    gw_board = new QGraphicsView(this);
    gw_newTile = new QGraphicsView(this);
    le_player = new QLineEdit(this);

    btn_size_5 = new QPushButton("5", this);
    btn_size_7 = new QPushButton("7", this);
    btn_size_9 = new QPushButton("9", this);
    btn_size_11 = new QPushButton("11", this);

    btn_play = new QPushButton("Play!", this);

    board = new Board();

    //zadne scroll bary
    gw_board->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_board->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_newTile->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_newTile->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::menu(){
    this->hideGame();

    l_addPlayers->setGeometry(QRect(250, 25, 40, 80));
    l_sizeView->setGeometry(QRect(20, 100, 90, 20));
    le_player->setGeometry(QRect(150, 20, 80, 20));

    l_size->setGeometry(QRect(20, 20, 60, 20));
    l_players->setGeometry(QRect(250, 20, 60, 20));

    btn_size_5->setGeometry(QRect(40, 40, 20, 20));
    btn_size_7->setGeometry(QRect(60, 40, 20, 20));
    btn_size_9->setGeometry(QRect(80, 40, 20, 20));
    btn_size_11->setGeometry(QRect(100, 40, 20, 20));

    btn_play->setGeometry(QRect(200, 140, 75, 40));

    btn_addPlayer->setGeometry(QRect(150, 50, 75, 23));      //tlacitko pridat hrace
    resize(500, 400);                       //cele okno

    ui->plainTextEdit->setGeometry(QRect(20, 220, 400, 150));    //debug okno

    //connections
    connect(btn_size_5, SIGNAL (released()), this, SLOT (handle_btn_size_5()));
    connect(btn_size_7, SIGNAL (released()), this, SLOT (handle_btn_size_7()));
    connect(btn_size_9, SIGNAL (released()), this, SLOT (handle_btn_size_9()));
    connect(btn_size_11, SIGNAL (released()), this, SLOT (handle_btn_size_11()));
    connect(btn_addPlayer, SIGNAL (released()), this, SLOT (handle_btn_addPlayer()));
    connect(btn_play, SIGNAL (released()), this, SLOT (handle_btn_play()));
}

void MainWindow::hideMenu(){
    btn_addPlayer->hide();
    l_sizeView->hide();
    le_player->hide();
    btn_size_5->hide();
    btn_size_7->hide();
    btn_size_9->hide();
    btn_size_11->hide();
    btn_play->hide();
}

void MainWindow::game(){

    this->hideMenu();
    this->showGame();

   //lokalni promenne
    unsigned int i;

    this->board->setBoard(this->size);   //vygenerovat kameny pro hraci desku
    this->board->setOutterFields(this->size);   //vygenerování policek pro vsunuti kamene
    this->board->setTreasures(this->quantity);   //vygenerovat poklady
    this->board->setCards(this->quantity);   //vygenerovat karty

    this->board->getCards()->shuffle();     //zamicha karty
    this->board->getTreasures()->shuffle(); //zamicha poklady

/* DEBUG */
    ui->plainTextEdit->appendPlainText("Generated tiles");
    ui->plainTextEdit->appendPlainText("Straight:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileStraight::count));
    ui->plainTextEdit->appendPlainText("Corner:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileCorner::count));
    ui->plainTextEdit->appendPlainText("Cross:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileCross::count));

    TreasurePack* tr_pom = this->board->getCards();

    ui->plainTextEdit->appendPlainText("\nCards:");

    for (i=0; i < quantity; ++i){
        ui->plainTextEdit->appendPlainText(QString::number(tr_pom->getTreasure(i)->getCode()));
    }

    tr_pom = this->board->getTreasures();

    ui->plainTextEdit->appendPlainText("\nTreasures:");
    for (i=0; i < quantity; ++i){
        ui->plainTextEdit->appendPlainText(QString::number(tr_pom->getTreasure(i)->getCode()));
    }

    //ui->plainTextEdit->appendPlainText("\nCoor.  Rot.  Move");
/* END DEBUG */

    gw_board->setInteractive(true);

    this->genBoard();

    this->width = this->size*IMG_SIZE+100;    //sirka sceny
    this->height = this->size*IMG_SIZE+100;   //vyska sceny

    //nastaveni zobrazovani objektu
    gw_board->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky
    btn_rotate->setGeometry(QRect(60, height+20, 50, 23));      //tlacitko rotace
    l_players->setGeometry(QRect(240, height+15, 80, 60));
    l_addPlayers->setGeometry(QRect(290, height+15, 80, 60));
    ui->plainTextEdit->setGeometry(QRect(width+20, 10, 250, height+25));    //debug okno
    gw_newTile->setGeometry(QRect(10, height+20, 44, 44));      //novy kamen mimo hraci desku
    resize(10+width+20+250, 10+height+25+40);                       //cele okno

    board->setNewTile();          //vygenerovani noveho kamenu mimo desku

    this->drawNewTile();        //zobrazi novy kamen

    gw_board->setScene(scene);  //zobrazi board

    //connections
    connect(btn_rotate, SIGNAL (released()), this, SLOT (handle_btn_rotate()));
}

void MainWindow::hideGame(){

    btn_rotate->hide();
    //ui->plainTextEdit->hide();
    gw_board->hide();
    gw_newTile->hide();

}

void MainWindow::showGame(){

    btn_rotate->show();
    //ui->plainTextEdit->show();
    gw_board->show();
    gw_newTile->show();
}

MainWindow::~MainWindow()
{
    delete this->board->getCards();
    delete this->board->getTreasures();

    delete scene;
    delete newTile;

    delete btn_rotate;
    delete btn_addPlayer;

    delete l_addPlayers;
    delete l_players;
    delete l_sizeView;

    delete gw_board;
    delete gw_newTile;
    delete le_player;
    delete board;

    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    if (event->button() == Qt::LeftButton){
        if(event->localPos().x() < 10 || event->localPos().y() < 10){return;}
        unsigned int posX = event->localPos().x()-10;
        unsigned int posY = event->localPos().y()-10;

        unsigned int width = this->gw_board->width();
        unsigned int height = this->gw_board->height();

        if((posX > 0 && posX < width) && (posY > 0 && posY < height)){

            if ((posX > width - 50 || posX < 50) || (posY > height - 50 || posY < 50))
            {
                //mimo hraci plochu

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

                    if (row % 2 == 0 && col % 2 == 0)
                    {
                        board->insertNewTile(QPoint(row, col));
                        this->genBoard();
                        this->drawNewTile();
                    }
                }
            }
            else
            {
                unsigned int row = (posY - 50) / IMG_SIZE;
                unsigned int col = (posX - 50) / IMG_SIZE;

                col = row;  //aby se nezobrazoval warning :D
            }
        }
    }
}

void MainWindow::handle_btn_rotate()
{
//    ui->plainTextEdit->appendPlainText("Obsluha Rotate");

    this->board->getNewTile()->rotate();   //otoceni

    //zavola prekresleni
    this->drawNewTile();
}

void MainWindow::handle_btn_addPlayer()
{
    unsigned int i, n;
    n = this->board->getNumPlayers();
    if (n >= 4){
       ui->plainTextEdit->appendPlainText("MAX 4 Players");
    }
    else{
        if (le_player->text().isEmpty()){
            this->board->addPlayer(Player());
        }
        else{
            for (i=0; i < n; ++i ){
                if(!(le_player->text().compare(board->getPlayer(i).getName()))){
                    ui->plainTextEdit->appendPlainText("Name already exists");
                    break;
                }
            }
            if(i == board->getNumPlayers()){
                this->board->addPlayer(Player(le_player->text()));
            }
        }

        //zavola prekresleni
        this->drawPlayers();
    }
}

void MainWindow::drawNewTile()
{
    this->newTile->addPixmap(board->getNewTile()->getImage());        //prida obrazek do okenka
    gw_newTile->setScene(newTile);  //zobrazi novy kamen
}

void MainWindow::drawPlayers()
{
    QString str;
    unsigned int i, n = board->getNumPlayers();
    for (i=0; i<n; ++i){
        str += board->getPlayer(i).getName() + "\n";
    }
    str.remove(str.length()-1,1);   //odstraneni posledniho znaku
    l_addPlayers->setText(str);
    l_addPlayers->repaint();
}

void MainWindow::handle_btn_size_5()
{
    this->size = 5;
    this->drawSize();
}

void MainWindow::handle_btn_size_7()
{
    this->size = 7;
    this->drawSize();
}

void MainWindow::handle_btn_size_9()
{
    this->size = 9;
    this->drawSize();
}

void MainWindow::handle_btn_size_11()
{
    this->size = 11;
    this->drawSize();
}

void MainWindow::drawSize(){
    QString str;
    str = "Choosen size: " + QString::number(this->size);
    l_sizeView->setText(str);
    l_sizeView->repaint();
}

void MainWindow::handle_btn_play()
{
    if(board->getNumPlayers() >= 2){
        this->board->setSize(this->size);
        this->board->setPlayerPos();
        this->game();
    }
    else{
        ui->plainTextEdit->appendPlainText("Restriction: 2-4 players needed for game");
    }
}

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
                obr = tile->getImage();
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
            obr = tile->getImage();     //ziska obrazek

/* DEBUG */
//                int rot, mov;
//                QPoint pos;
//                pos = tile->getPosition();
//                rot = tile->getRotation();
//                mov = tile->getMove();

//                ui->plainTextEdit->appendPlainText(QString::number(pos.x()+1));
//                ui->plainTextEdit->insertPlainText("x");
//                ui->plainTextEdit->insertPlainText(QString::number(pos.y()+1));
//                ui->plainTextEdit->insertPlainText(" :    ");
//                ui->plainTextEdit->insertPlainText(QString::number(rot));
//                ui->plainTextEdit->insertPlainText("        ");
//                ui->plainTextEdit->insertPlainText(QString::number(mov));
/* END DEBUG */

            pixmapItem = scene->addPixmap(obr); //prida obrazek do sceny a vrati odkaz na nej

            pixmapItem->setX(x+50);
            pixmapItem->setY(y+50);

            //vykresleni gracu
            if (i == 0 || j == 0 || i == this->size-1 || j == this->size-1){    //podminka pro zrychleni
                for (l=0; l < board->getNumPlayers(); ++l){
                    Player* p;
                    p = &board->getPlayer(l);
                    if (i == p->getPosition().x() && j == p->getPosition().y()){
                        obr = p->getImage();
                        pixmapItem = scene->addPixmap(obr); //prida obrazek do sceny a vrati odkaz na nej

                        pixmapItem->setX(x+50);
                        pixmapItem->setY(y+50);
                    }
                }
            }

            x += IMG_SIZE; //posunuti v ose X
        }
        /* Odradkovani */
        x = 0;
        y += IMG_SIZE;  //posunuti v ose Y
    }
}
