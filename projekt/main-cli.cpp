//ICP-Labyrinth 2014/2015
/**
* @file       main-cli.cpp
* @author     Jakub Pastuszek (xpastu00@stud.fit.vutr.cz)
* @date       May 2015
*
* CLI demonstration program -> execute main CLI window
*/

#include "maincli.h"
#include <QTextStream>

int main(){//int argc, char* argv[]
    QTextStream streamIn(stdin);
    QString s;
    MainCLI m;

    bool konec = false;

    m.help();

    m.game();

    while (!konec){

        m.u_getShift();

        m.u_getMove();

        QTextStream(stdout) << "END (Y): ";
        s = streamIn.readLine();
        if(s == "Y" || s == "y"){konec = true;}
    }
}
