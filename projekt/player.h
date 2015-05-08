#ifndef PLAYER
#define PLAYER

#include <QPoint>
#include <QString>

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
    void setName(QString);

    QString getName();
    unsigned int getPoints();

    void addPoints(unsigned int);

    void run();

    bool operator == (const Player&) const;

    static unsigned int countNoName;

    //~Player();
};

#endif // PLAYER

