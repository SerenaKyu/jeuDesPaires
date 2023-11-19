a.out : ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o
	gcc -o a.out ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o -lncurses

../Code/ObjectFile/main.o : ../Code/main.c
	gcc -c -Wall ../Code/main.c -o ../Code/ObjectFile/main.o

../Code/ObjectFile/menu.o : ../Code/menu.c
	gcc -c -Wall ../Code/menu.c -o ../Code/ObjectFile/menu.o

clean :
	rm -f prog ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o a.out
