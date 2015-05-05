
class tileStraight{

};

class tileCorner{

};

class tileCross{

};

class tile{

};

class player{
    int x;
    int y;
    int points;
    //predmety sesbirane
    //aktualni karta
public:
    player(): points {0} {}
};

class game{
    int size;
    int players;
    //INIT
public:
    game(): size{5} {}
    game(int size) {
        if (size%2 == 0 && size >= 5 && size <= 11) {
            this->size = size;
        }
    }
    player* makePlayer();
};

player* game::makePlayer() {
	player *p = new player();
	
	if (players == 4) {
        //chyba moc hracu
    }
    players++;

	return p;
}

class card{

};

class move{

};
