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

    void menu();
    void hideMenu();

    void game();
    void hideGame();
    void showGame();

    void drawNewTile();
    void drawPlayers();
    void drawSize();

private slots:
    void handle_btn_rotate();

    void handle_btn_size_5();
    void handle_btn_size_7();
    void handle_btn_size_9();
    void handle_btn_size_11();
    void handle_btn_addPlayer();

private:
    Ui::MainWindow *ui;

    unsigned int endMenu;
    unsigned int size;
    unsigned int numPlayers;

    int width, height;

    Board board;

    QGraphicsScene *scene;
    QGraphicsScene *newTile;

    QPushButton *btn_rotate;
    QPushButton *btn_addPlayer;

    QLabel* l_addPlayers;
    QLabel* l_players;
    QLabel* l_sizeView;
};

#endif // MAINWINDOW_H
