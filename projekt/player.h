#include <QPoint>
#include <QString>

#ifndef PLAYER
#define PLAYER

class Player
{
    QPoint position;
    QString name;
    unsigned int points;
    //QVector<Card> cards;
public:
    Player();
    Player(QString);     //jmeno hráče
    Player(QString, QPoint position);     //jméno hráče a jeho výchozí pozice

    void setPosition(QPoint);
    QPoint getPosition();
    void run();
    void setName(QString);
    QString getName();
    unsigned int getPoints();
    void addPoints(unsigned int);

    ~Player();
};

#endif // PLAYER

