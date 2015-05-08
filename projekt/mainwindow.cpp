#include "mainwindow.h"
#include "ui_mainwindow.h"

const unsigned int SIZE = 7;
const unsigned int IMG_SIZE = 44;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(qrand()); //pro testovani
    //qsrand(QTime::currentTime().msec());    //random

    ui->setupUi(this);

    //GUI objekty
    scene = new QGraphicsScene();
    newTile = new QGraphicsScene();
    btn_rotate = new QPushButton("Rotate", this);
    btn_addPlayer = new QPushButton("Add Player", this);

    //lokalni promenne
    QGraphicsPixmapItem *pixmapItem;
    QPixmap obr;

    this->board.setBoard(SIZE);   //vygenerovat kameny pro hraci desku

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
    int i, j;
    int x = 0, y = 0, k = 0, a, b;

    ui->graphicsView->setInteractive(true);

    /* Generovani kamenu hraci desky */
    for (i=0; i < SIZE; ++i){
        for (j=0; j < SIZE; ++j){
            //pozice moznych vstupu kamenu
            if(((i==0 || i==(SIZE-1)) && j%2==1) || ((j==0 || j==(SIZE-1)) && i%2==1)){
                tile = board.getOutterField(k);
                k++;
                obr = tile->getImage();
                pixmapItem = scene->addPixmap(obr);
                a=x;
                b=y;
                if(i==0){a=x+50;}
                else if(i==(SIZE-1)){a=x+50;b=y+100;}
                if(j==0){b=y+50;}
                else if(j==(SIZE-1)){b=y+50;a=x+100;}
                pixmapItem->setX(a);
                pixmapItem->setY(b);
            }
            int souradnice = j+i*SIZE;
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

    this->width = SIZE*IMG_SIZE+100;    //sirka sceny
    this->height = SIZE*IMG_SIZE+100;   //vyska sceny

    //nastaveni zobrazovani objektu
    ui->graphicsView->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky
    btn_rotate->setGeometry(QRect(60, height+20, 50, 23));      //tlacitko rotace
    btn_addPlayer->setGeometry(QRect(150, height+20, 75, 23));      //tlacitko pridat hrace
    ui->l_players->setGeometry(QRect(240, height+15, 80, 60));
    ui->plainTextEdit->setGeometry(QRect(width+20, 10, 250, height+25));    //debug okno
    ui->gw_newTile->setGeometry(QRect(10, height+20, 44, 44));      //novy kamen mimo hraci desku
    resize(10+width+20+250, 10+height+25+40);                       //cele okno

    board.setNewTile();          //vygenerovani noveho kamenu mimo desku

    this->drawNewTile();        //zobrazi novy kamen

    ui->graphicsView->setScene(scene);  //zobrazi board

    //connections
    connect(btn_rotate, SIGNAL (released()), this, SLOT (handle_btn_rotate()));
    connect(btn_addPlayer, SIGNAL (released()), this, SLOT (handle_btn_addPlayer()));
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

    //tady se zpracuje udalost
    QMessageBox msgBox;
    msgBox.setWindowTitle("Kliknul jsi na obrázek");
    msgBox.setText(QString::number(round(((event->localPos().y()-50)-IMG_SIZE/2)/IMG_SIZE)+1) + " " + QString::number(round((event->localPos().x()-IMG_SIZE/2)/IMG_SIZE)));
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
    if (this->board.getNumPlayers() >= 4){
       ui->plainTextEdit->appendPlainText("MAX 4 Players");
    }
    else{
        Player player = Player();
        this->board.addPlayer(player);

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
    ui->l_players->setText(str);
    ui->l_players->repaint();
}
