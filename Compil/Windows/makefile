game.exe : ../../Code-Win/ObjectFile/main.o ../../Code-Win/ObjectFile/menu.o ../../Code-Win/ObjectFile/game.o ../../Code-Win/ObjectFile/aftergame.o ./pdcurses.dll
	gcc -o game.exe ../../Code-Win/ObjectFile/main.o ../../Code-Win/ObjectFile/menu.o ../../Code-Win/ObjectFile/game.o ../../Code-Win/ObjectFile/aftergame.o -L. -l:pdcurses.dll

../../Code-Win/ObjectFile/main.o : ../../Code-Win/main.c
	gcc -c -Wall ../../Code-Win/main.c -o ../../Code-Win/ObjectFile/main.o

../../Code-Win/ObjectFile/menu.o : ../../Code-Win/menu.c
	gcc -c -Wall ../../Code-Win/menu.c -o ../../Code-Win/ObjectFile/menu.o

../../Code-Win/ObjectFile/aftergame.o : ../../Code-Win/aftergame.c
	gcc -c -Wall ../../Code-Win/aftergame.c -o ../../Code-Win/ObjectFile/aftergame.o

../../Code-Win/ObjectFile/game.o : ../../Code-Win/game.c
	gcc -c -Wall ../../Code-Win/game.c -o ../../Code-Win/ObjectFile/game.o

clean :
	rm -f ../../Code-Win/ObjectFile/main.o ../../Code-Win/ObjectFile/menu.o ../../Code-Win/ObjectFile/game.o ../../Code-Win/ObjectFile/aftergame.o game.exe
