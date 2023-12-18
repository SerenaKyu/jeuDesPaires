game.exe : ../../Code/ObjectFile/main.o ../../Code/ObjectFile/menu.o ../../Code/ObjectFile/game.o ../../Code/ObjectFile/aftergame.o ../../Code/ObjectFile/card.o 
	gcc -o game.exe ../../Code/ObjectFile/main.o ../../Code/ObjectFile/menu.o ../../Code/ObjectFile/game.o ../../Code/ObjectFile/aftergame.o ../../Code/ObjectFile/card.o -lncurses

../../Code/ObjectFile/main.o : ../../Code/main.c
	gcc -c -Wall ../../Code/main.c -o ../../Code/ObjectFile/main.o

../../Code/ObjectFile/menu.o : ../../Code/menu.c
	gcc -c -Wall ../../Code/menu.c -o ../../Code/ObjectFile/menu.o

../../Code/ObjectFile/aftergame.o : ../../Code/aftergame.c
	gcc -c -Wall ../../Code/aftergame.c -o ../../Code/ObjectFile/aftergame.o

../../Code/ObjectFile/game.o : ../../Code/game.c
	gcc -c -Wall ../../Code/game.c -o ../../Code/ObjectFile/game.o

../../Code/ObjectFile/card.o : ../../Code/card.c
	gcc -c -Wall ../../Code/card.c -o ../../Code/ObjectFile/card.o

clean :
	rm -f ../../Code/ObjectFile/main.o ../../Code/ObjectFile/menu.o ../../Code/ObjectFile/game.o ../../Code/ObjectFile/aftergame.o ../../Code/ObjectFile/card.o game.exe
