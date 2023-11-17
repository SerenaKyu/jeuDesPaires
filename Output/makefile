a.out : ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o
	gcc -o a.out ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o -lncurses

main.o : ../Code/main.c
	gcc -c -Wall ../Code/main.c

menu.o : ../Code/menu.c
	gcc -c -Wall ../Code/menu.c

clean :
	rm -f prog ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o a.out