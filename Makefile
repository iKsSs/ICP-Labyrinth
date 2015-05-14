PROJECT = labyrinth2015

CC = g++
RM = rm -rf
ZIP = zip

STD_CPP11 = -std=c++11

CFLAGS = -O2 $(STD_CPP11) -s -Wall -Wextra -c

LFAGS =  -static-libstdc++

SRC = src

ZIP_FILE = xpastu00-xnikdo99-100-0.zip

PACKED_FILES = Doxyfile Makefile src src/images src/images/treasure examples doc README.txt

all:  labyrinth labyrinth-cli

#labyrinth-cli: $(SRC)/board.o $(SRC)/card.o $(SRC)/player.o $(SRC)/tile.o $(SRC)/main-cli.o
#	$(CC) -O2 -s -o $@ $(SRC)/board.o $(SRC)/card.o  $(SRC)/player.o  $(SRC)/tile.o $(SRC)/main-cli.o $(LFAGS)

$(SRC)/board.o: $(SRC)/board.cpp
	$(CC) $(CFLAGS) -o $@ $<

$(SRC)/card.o: $(SRC)/card.cpp
	$(CC) $(CFLAGS) -o $@ $<

$(SRC)/main-cli.o: $(SRC)/main-cli.cpp
	$(CC) $(CFLAGS) -o $@ $<

$(SRC)/player.o: $(SRC)/player.cpp
	$(CC) $(CFLAGS) -o $@ $<

$(SRC)/tile.o: $(SRC)/tile.cpp
	$(CC) $(CFLAGS) -o $@ $<	
	
labyrinth:
	export PATH=/usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/:$$PATH
	/usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake ./src/projekt.pro -o Makefile-gui
	mv Makefile-gui ./src/
	make -f ./src/Makefile-gui

labyrinth-cli:
	export PATH=/usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/:$$PATH
	/usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake ./src/projekt-cli.pro -o Makefile-cli
	mv Makefile-cli ./src/
	make -f ./src/Makefile-cli	
	
run:
	./labyrinth2015

pack:
	$(ZIP) -r $(ZIP_FILE) $(PACKED_FILES)

doxygen:
	doxygen Doxyfile

clean:
	$(RM) Makefile-gui $(SRC)/Makefile-gui Makefile-cli $(SRC)/Makefile-cli Doxyfile.bak $(SRC)/moc_*  *.o $(SRC)/*.o moc_* ui_* *.o *.cpp *.h
	


