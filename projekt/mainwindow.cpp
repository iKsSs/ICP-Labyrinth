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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsPixmapItem *pixmapItem;
    QPixmap obr;

    Board board;

    board.setBoard(2);

    int i;
    int n = 4;
    for (i=0; i < n; ++i){
        obr = board.getTile(n-1-i).getImage();
        scene->addPixmap(obr);
        pixmapItem = scene->addPixmap(obr);
        pixmapItem->moveBy(44*i, 0);
    }

    ui->plainTextEdit->appendPlainText("test");

    this->width = ui->graphicsView->width();
    this->height = ui->graphicsView->height();

    scene->addPixmap(obr);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
