#include "mainwindow.h"
#include "ui_mainwindow.h"

const unsigned int IMG_SIZE = 44;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(qrand()); //pro testovani
    //qsrand(QTime::currentTime().msec());    //random

    ui->setupUi(this);

    this->size = 7;
    this->numPlayers = 0;

    //GUI objekty
    scene = new QGraphicsScene(this);
    newTile = new QGraphicsScene();
    l_players = new QLabel(this);
    btn_rotate = new QPushButton("Rotate", this);
    btn_addPlayer = new QPushButton("Add Player", this);
    gw_board = new QGraphicsView(this);

    //zadne scroll bary
    gw_board->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gw_board->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->menu();
    //this->game();
}

void MainWindow::menu(){
    this->hideGame();

    btn_addPlayer->setGeometry(QRect(150, 50, 75, 23));      //tlacitko pridat hrace
    resize(500, 500);                       //cele okno

    l_addPlayers = new QLabel(this);
    l_addPlayers->setGeometry(QRect(250, 25, 40, 80));

    le_player = new QLineEdit(this);
    le_player->setGeometry(QRect(150, 20, 80, 20));

    QLabel* l_size = new QLabel("Choose size:", this);
    l_size->setGeometry(QRect(20, 20, 60, 20));

    QLabel* l_players = new QLabel("Players:", this);
    l_players->setGeometry(QRect(250, 20, 60, 20));

    l_sizeView = new QLabel("Choosen size: " + QString::number(this->size), this);
    l_sizeView->setGeometry(QRect(20, 100, 90, 20));

    QPushButton* btn_size_5 = new QPushButton("5", this);
    btn_size_5->setGeometry(QRect(40, 40, 25, 20));

    QPushButton* btn_size_7 = new QPushButton("7", this);
    btn_size_7->setGeometry(QRect(60, 40, 25, 20));

    QPushButton* btn_size_9 = new QPushButton("9", this);
    btn_size_9->setGeometry(QRect(80, 40, 25, 20));

    QPushButton* btn_size_11 = new QPushButton("11", this);
    btn_size_11->setGeometry(QRect(100, 40, 25, 20));

    QPushButton* btn_play = new QPushButton("Play!", this);
    btn_play->setGeometry(QRect(200, 140, 75, 40));

    //this->hideMenu();

    //connections
    connect(btn_size_5, SIGNAL (released()), this, SLOT (handle_btn_size_5()));
    connect(btn_size_7, SIGNAL (released()), this, SLOT (handle_btn_size_7()));
    connect(btn_size_9, SIGNAL (released()), this, SLOT (handle_btn_size_9()));
    connect(btn_size_11, SIGNAL (released()), this, SLOT (handle_btn_size_11()));
    connect(btn_addPlayer, SIGNAL (released()), this, SLOT (handle_btn_addPlayer()));
}

void MainWindow::hideMenu(){
    btn_addPlayer->hide();
    l_addPlayers->hide();
}

void MainWindow::game(){

    this->showGame();

    //lokalni promenne
    QGraphicsPixmapItem *pixmapItem;
    QPixmap obr;

    this->board.setBoard(this->size);   //vygenerovat kameny pro hraci desku

/* DEBUG */
    ui->plainTextEdit->appendPlainText("Generated tiles");
    ui->plainTextEdit->appendPlainText("Straight:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileStraight::count));
    ui->plainTextEdit->appendPlainText("Corner:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileCorner::count));
    ui->plainTextEdit->appendPlainText("Cross:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileCross::count));

    ui->plainTextEdit->appendPlainText("\nCoor.  Rot.  Move");
/* END DEBUG */

    //lokalni promenne
    Tile * tile;
    unsigned int i, j;
    int x = 0, y = 0, k = 0, a, b;

    gw_board->setInteractive(true);

    /* Generovani kamenu hraci desky */
    for (i=0; i < this->size; ++i){
        for (j=0; j < this->size; ++j){
            //pozice moznych vstupu kamenu
            if(((i==0 || i==(this->size-1)) && j%2==1) || ((j==0 || j==(this->size-1)) && i%2==1)){
                tile = board.getOutterField(k);
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
            tile = board.getTile(souradnice);    //odkaz na kamen
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

            x += IMG_SIZE; //posunuti v ose X
        }
        /* Odradkovani */
        x = 0;
        y += IMG_SIZE;  //posunuti v ose Y
    }

    this->width = this->size*IMG_SIZE+100;    //sirka sceny
    this->height = this->size*IMG_SIZE+100;   //vyska sceny

    //nastaveni zobrazovani objektu
   // ui->graphicsView->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky
    gw_board->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky

    btn_rotate->setGeometry(QRect(60, height+20, 50, 23));      //tlacitko rotace
    l_players->setGeometry(QRect(240, height+15, 80, 60));
    ui->plainTextEdit->setGeometry(QRect(width+20, 10, 250, height+25));    //debug okno
    ui->gw_newTile->setGeometry(QRect(10, height+20, 44, 44));      //novy kamen mimo hraci desku
    resize(10+width+20+250, 10+height+25+40);                       //cele okno

    board.setNewTile();          //vygenerovani noveho kamenu mimo desku

    this->drawNewTile();        //zobrazi novy kamen

    gw_board->setScene(scene);  //zobrazi board

    //connections
    connect(btn_rotate, SIGNAL (released()), this, SLOT (handle_btn_rotate()));
}

void MainWindow::hideGame(){
    gw_board->hide();
    btn_rotate->hide();
    l_players->hide();
    //ui->plainTextEdit->hide();
    ui->gw_newTile->hide();
}

void MainWindow::showGame(){
    gw_board->show();
    btn_rotate->show();
    l_players->show();
    //ui->plainTextEdit->show();
    ui->gw_newTile->show();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete newTile;
    delete btn_rotate;
    delete btn_addPlayer;
    delete ui;
}

void QGraphicsView::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    unsigned int posX = event->localPos().x();
    unsigned int posY = event->localPos().y();

    unsigned int row = (posY - 50) / IMG_SIZE;
    unsigned int col = (posX - 50) / IMG_SIZE;

    //tady se zpracuje udalost
    QMessageBox msgBox;
    msgBox.setWindowTitle("Kliknul jsi na obrázek");
    msgBox.setText(QString::number(row) + " " + QString::number(col));
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.exec();
}

void MainWindow::handle_btn_rotate()
{
    ui->plainTextEdit->appendPlainText("Obsluha Rotate");

    this->board.getNewTile()->rotate();   //otoceni

    //zavola prekresleni
    this->drawNewTile();
}

void MainWindow::handle_btn_addPlayer()
{
    unsigned int i;
    if (this->board.getNumPlayers() >= 4){
       ui->plainTextEdit->appendPlainText("MAX 4 Players");
    }
    else{
        if (le_player->text().isEmpty()){
            this->board.addPlayer(Player());
        }
        else{
            for (i=0; i < board.getNumPlayers(); ++i ){
                if(!(le_player->text().compare(board.getPlayer(i).getName()))){
                    ui->plainTextEdit->appendPlainText("Name already exists");
                    break;
                }
            }
            if(i == board.getNumPlayers()){
                this->board.addPlayer(Player(le_player->text()));
            }
        }

        //zavola prekresleni
        this->drawPlayers();
    }
}

void MainWindow::drawNewTile()
{
    this->newTile->addPixmap(board.getNewTile()->getImage());        //prida obrazek do okenka
    ui->gw_newTile->setScene(newTile);  //zobrazi novy kamen
}

void MainWindow::drawPlayers()
{
    QString str;
    unsigned int i, n = board.getNumPlayers();
    for (i=0; i<n; ++i){
        str += board.getPlayer(i).getName() + "\n";
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
