a.out: main.o Game.o ReadFile.o WriteFile.o PNG.o
	cc  main.o Game.o ReadFile.o WriteFile.o PNG.o -lpng

main.o: main.c Game.h ReadFile.h
	cc -c main.c
	
Game.o: Game.c Game.h WriteFile.h PNG.h
	cc -c Game.c -lpng

ReadFile.o: ReadFile.c ReadFile.h
	cc -c ReadFile.c

WriteFile.o: WriteFile.c WriteFile.h
	cc -c WriteFile.c
PNG.o: PNG.c PNG.h
	cc -c PNG.c -lpng
