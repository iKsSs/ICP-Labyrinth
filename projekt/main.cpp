/*
    Autor:      Jakub Pastuszek, xpastu00
    Projekt:    ICP-Labyrinth 2014/2015
    Datum:      Kveten 2015

    Popis:      hlavni program -> spusteni hlavniho zobrazovaciho okna

*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();


    w.menu();

   // w.game();

    return a.exec();
}
