#include "mainwindow.h"
#include "ui_mainwindow.h"

const unsigned int SIZE = 7;
const unsigned int IMG_SIZE = 44;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //qsrand(qrand()); //pro testovani
    qsrand(QTime::currentTime().msec());    //random

    ui->setupUi(this);

    scene = new QGraphicsScene();
    newTile = new QGraphicsScene();
    btn_rotate = new QPushButton("Rotate", this);

    //lokalni promenne
    QGraphicsPixmapItem *pixmapItem;
    QPixmap obr;

    board.setBoard(SIZE);   //vygenerovat kameny pro hraci desku

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
    int rot, mov;
    QPoint pos;
    int i;
    int j = 0, k = 0;
    int n = SIZE*SIZE;

    ui->graphicsView->setInteractive(true);

    /* Generovani kamenu hraci desky */
    for (i=0, j=0; i < n; ++i, ++j){

        tile = board.getTile(i);    //odkaz na kamen
        obr = tile->getImage();     //ziska obrazek

/* DEBUG */
        pos = tile->getPosition();
        rot = tile->getRotation();
        mov = tile->getMove();

        ui->plainTextEdit->appendPlainText(QString::number(pos.x()+1));
        ui->plainTextEdit->insertPlainText("x");
        ui->plainTextEdit->insertPlainText(QString::number(pos.y()+1));
        ui->plainTextEdit->insertPlainText(" :    ");
        ui->plainTextEdit->insertPlainText(QString::number(rot));
        ui->plainTextEdit->insertPlainText("        ");
        ui->plainTextEdit->insertPlainText(QString::number(mov));
/* END DEBUG */

        pixmapItem = scene->addPixmap(obr); //prida obrazek do sceny a vrati odkaz na nej

        /* Odradkovani */
        if(i%SIZE == 0){
            k += IMG_SIZE;  //posunuti v ose Y
            j = 0;          //posunuti v ose X
        }
        pixmapItem->moveBy(IMG_SIZE*j, k);  //premisteni v X,Y
    }

    this->width = SIZE*IMG_SIZE;    //sirka sceny
    this->height = SIZE*IMG_SIZE;   //vyska sceny

    //nastaveni zobrazovani objektu
    ui->graphicsView->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky
    btn_rotate->setGeometry(QRect(60, height+20, 50, 23));      //tlacitko rotace
  //  ui->btn_rotate->setGeometry(QRect(60, height+20, 50, 23));      //tlacitko rotace
    ui->btn_addPlayer->setGeometry(QRect(150, height+20, 75, 23));  //tlacitko pridat hrace
    ui->plainTextEdit->setGeometry(QRect(width+20, 10, 250, height+25));    //debug okno
    ui->gw_newTile->setGeometry(QRect(10, height+20, 44, 44));      //novy kamen mimo hraci desku
    resize(10+width+20+250, 10+height+25+40);                       //cele okno

    board.genNewTile();          //vygenerovani noveho kamenu mimo desku
    tile = board.getNewTile();   //odkaz na nove vygenerovany kamen
 //   tile->rotate();
    obr = tile->getImage();      //ziska obrazek noveho kamene

    newTile->addPixmap(obr);        //prida obrazek do okenka

    ui->graphicsView->setScene(scene);  //zobrazi board
    ui->gw_newTile->setScene(newTile);  //zobrazi novy kamen

    //connections
    connect(btn_rotate, SIGNAL (pressed()), this, SLOT (handle_btn_rotate()));
}

MainWindow::~MainWindow()
{
    delete scene;
    delete newTile;
    delete ui;
}

void QGraphicsView::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    //tady se zpracuje udalost
    QMessageBox msgBox;
    msgBox.setWindowTitle("Kliknul jsi na obrázek");
    msgBox.setText(QString::number(round((event->localPos().x()-IMG_SIZE/2)/IMG_SIZE)+1) + " " + QString::number(round((event->localPos().y()-IMG_SIZE/2)/IMG_SIZE)+1));
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.exec();
}

void MainWindow::handle_btn_rotate()
{
    ui->plainTextEdit->appendPlainText("Obsluha Rotate");

  //  Tile* tile = board.getNewTile();   //odkaz na kamen mimo desku
   // tile->rotate();                     //otoceni

    //zavola prekresleni
    void drawNewTile();
}

void MainWindow::drawNewTile()
{
    newTile->addPixmap(board.getNewTile()->getImage());        //prida obrazek do okenka
    ui->gw_newTile->setScene(newTile);  //zobrazi novy kamen
}
