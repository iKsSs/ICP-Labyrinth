/**
 * @file       mainwindow.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @project    ICP-Labyrinth 2014/2015
 * @date       May 2015
 *
 * Hlavicky funkci pro zobrazeni hlavniho okna aplikace
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QLabel>
#include <QPoint>
#include <QVector>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QMouseEvent>

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
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

    void menu();
    void hideMenu();

    void game();
    void hideGame();
    void showGame();

    void drawNewTile();
    void drawPlayers();
    void drawSize();
    void drawQuantity();

    void genBoard();

    bool canMove(unsigned int, unsigned int);

private slots:
    void handle_btn_rotate();

    void handle_btn_size_5();
    void handle_btn_size_7();
    void handle_btn_size_9();
    void handle_btn_size_11();
    void handle_btn_addPlayer();
    void handle_btn_play();

    void handle_btn_quantity_12();
    void handle_btn_quantity_24();

private:
    Ui::MainWindow *ui;

    unsigned int quantity;
    unsigned int size;
    unsigned int numPlayers;

    unsigned int width, height;

    Board *board;

    QGraphicsScene *scene;
    QGraphicsScene *newTile;

    QPushButton *btn_rotate;
    QPushButton *btn_addPlayer;

    QLabel* l_addPlayers;
    QLabel* l_players;
    QLabel* l_sizeView;
    QLabel* l_quantityView;

    QGraphicsView* gw_board;
    QGraphicsView* gw_newTile;

    QLabel* l_size;
    QLabel* l_quantity;
    QLineEdit* le_player;

    QPushButton* btn_quantity_12;
    QPushButton* btn_quantity_24;
    QPushButton* btn_size_5;
    QPushButton* btn_size_7;
    QPushButton* btn_size_9;
    QPushButton* btn_size_11;
    QPushButton* btn_play;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
