//ICP-Labyrinth 2014/2015
/**
 * @file       main.cpp
 * @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
 * @date       May 2015
 *
 * Main program -> execute main imaging window
 */

/** @mainpage Project Labyrinth: VUT FIT ICP 2014/2015
*   @par Author:
*    Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
*   @par Description:
*   - Well known board game Labyrinth implemented in C++ with Qt toolkit.
*
*/


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    w.menu();

    return a.exec();
}
