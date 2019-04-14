a.out: main.o Game.o ReadFile.o WriteFile.o PNG.o
	gcc  main.o Game.o ReadFile.o WriteFile.o PNG.o -lpng

main.o: main.c Game.h ReadFile.h WriteFile.h
	gcc -c main.c
	
Game.o: Game.c Game.h WriteFile.h PNG.h
	gcc -c Game.c -lpng

ReadFile.o: ReadFile.c ReadFile.h Game.h
	gcc -c ReadFile.c

WriteFile.o: WriteFile.c WriteFile.h Game.h
	gcc -c WriteFile.c

PNG.o: PNG.c PNG.h Game.h
	gcc -c PNG.c -lpng
