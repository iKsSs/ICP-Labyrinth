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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //qsrand(qrand()); //pro testovani
    qsrand(QTime::currentTime().msec());

    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();
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

    ui->graphicsView->setInteractive(true);

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

//    this->width = ui->graphicsView->width();
//    this->height = ui->graphicsView->height();

    this->width = size*44;
    this->height = size*44;

    ui->graphicsView->setGeometry(QRect(10, 10, width, height));    //prizpusobeni okna hraci desky
    ui->btn_rotate->setGeometry(QRect(50, height+20, 50, 23));
    ui->btn_addPlayer->setGeometry(QRect(150, height+20, 75, 23));
    ui->plainTextEdit->setGeometry(QRect(width+20, 10, 250, height+25));
    resize(10+width+20+250, 10+height+25+20);

    ui->graphicsView->setScene(scene);
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
    msgBox.setText(QString::number(event->localPos().x()) + " " + QString::number(event->localPos().y()));
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.exec();
}
