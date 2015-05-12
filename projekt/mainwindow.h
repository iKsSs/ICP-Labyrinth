//ICP-Labyrinth 2014/2015
/**
 * @file       mainwindow.h
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Function headers for show main application window.
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
#include <QFileDialog>

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

/*! Class representing MainWindow */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void menu();        //!< start menu
    void hideMenu();    //!< hide menu objects

    void load();
    void game();        //!< start game
    void hideGame();    //!< hide game objects
    void showGame();    //!< show game objects

    void drawNewTile();
    void drawCard(Player *);
    void drawPlayers();
    void drawSize();
    void drawQuantity();

    void genBoard();    //!< generate game board

    bool canMove(int, int);   //!< look for path from start_index to end_index

private slots:
    void handle_btn_rotate();

    void handle_btn_size_5();
    void handle_btn_size_7();
    void handle_btn_size_9();
    void handle_btn_size_11();
    void handle_btn_addPlayer();
    void handle_btn_save();
    void handle_btn_load();
    void handle_btn_undo();
    void handle_btn_play();

    void handle_btn_quantity_12();
    void handle_btn_quantity_24();

private:
    Ui::MainWindow *ui;

    unsigned int quantity;
    unsigned int size;

    unsigned int width, height;

    Board *board;

    QGraphicsScene *scene;
    QGraphicsScene *newTile;
    QGraphicsScene *card;

    QPushButton *btn_rotate;
    QPushButton *btn_addPlayer;

    QLabel* l_addPlayers;
    QLabel* l_players;
    QLabel* l_sizeView;
    QLabel* l_quantityView;

    QGraphicsView* gw_board;
    QGraphicsView* gw_newTile;
    QGraphicsView* gw_card;

    QLabel* l_size;
    QLabel* l_quantity;
    QLabel* l_player_res;
    QLineEdit* le_player;

    QPushButton* btn_quantity_12;
    QPushButton* btn_quantity_24;
    QPushButton* btn_size_5;
    QPushButton* btn_size_7;
    QPushButton* btn_size_9;
    QPushButton* btn_size_11;
    QPushButton* btn_save;
    QPushButton* btn_load;
    QPushButton* btn_undo;
    QPushButton* btn_play;

protected:
    void mousePressEvent(QMouseEvent *event);   //!< handle mouse click event
};

#endif // MAINWINDOW_H
