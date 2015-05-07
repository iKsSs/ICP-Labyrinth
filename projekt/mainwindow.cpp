#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QMouseEvent>

#include "board.h"

const unsigned int SIZE = 7;
const unsigned int IMG_SIZE = 44;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //qsrand(qrand()); //pro testovani
    qsrand(QTime::currentTime().msec());    //random

    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsScene *newTile = new QGraphicsScene();
    QGraphicsPixmapItem *pixmapItem;
    QPixmap obr;

    Board board;

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

    ui->graphicsView->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky
    ui->btn_rotate->setGeometry(QRect(60, height+20, 50, 23));      //tlacitko rotace
    ui->btn_addPlayer->setGeometry(QRect(150, height+20, 75, 23));  //tlacitko pridat hrace
    ui->plainTextEdit->setGeometry(QRect(width+20, 10, 250, height+25));    //debug okno
    ui->gw_newTile->setGeometry(QRect(10, height+20, 44, 44));      //novy kamen mimo hraci desku
    resize(10+width+20+250, 10+height+25+40);                       //cele okno

    board.genNewTile();          //vygenerovani noveho kamenu mimo desku
    tile = board.getNewTile();   //odkaz na nove vygenerovany kamen
    obr = tile->getImage();      //ziska obrazek noveho kamene

    pixmapItem = newTile->addPixmap(obr);

    ui->graphicsView->setScene(scene);
    ui->gw_newTile->setScene(newTile);
}

MainWindow::~MainWindow()
{
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
