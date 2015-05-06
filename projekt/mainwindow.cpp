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

#include "board.h"

const unsigned int SIZE = 7;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsPixmapItem *pixmapItem;
    QPixmap obr;

    Board board;

    board.setBoard(SIZE);

    ui->plainTextEdit->appendPlainText("Generated tiles");
    ui->plainTextEdit->appendPlainText("Straight:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileStraight::count));
    ui->plainTextEdit->appendPlainText("Corner:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileCorner::count));
    ui->plainTextEdit->appendPlainText("Cross:\t");
    ui->plainTextEdit->insertPlainText(QString::number(TileCross::count));

    Tile * tile;
    int rot, mov;
    QPoint pos;
    int i;
    int j = 0, k = 0;
    int size = SIZE;
    int n = size*size;

    ui->plainTextEdit->appendPlainText("\nCoor.  Rot.  Move");

    for (i=0, j=0; i < n; ++i, ++j){

        tile = board.getTile(i);
        obr = tile->getImage();

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

        pixmapItem = scene->addPixmap(obr);

        if(i%size == 0){
            k += 44;
            j = 0;
        }
        pixmapItem->moveBy(44*j, k);
    }

    //ui->plainTextEdit->appendPlainText("test");

    this->width = ui->graphicsView->width();
    this->height = ui->graphicsView->height();


    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
