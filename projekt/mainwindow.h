#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include <QMainWindow>
#include <QPushButton>
#include <QCoreApplication>

#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void drawNewTile();

private slots:
    void handle_btn_rotate();

private:
    Ui::MainWindow *ui;

    int width, height;

    Board board;

    QGraphicsScene *scene;
    QGraphicsScene *newTile;

    QPushButton *btn_rotate;
};

#endif // MAINWINDOW_H
