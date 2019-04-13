a.out: main.o Game.o ReadFile.o WriteFile.o
	cc  main.o Game.o ReadFile.o WriteFile.o

main.o: main.c Game.h ReadFile.h
	cc -c main.c
	
Game.o: Game.c Game.h WriteFile.h
	cc -c Game.c

ReadFile.o: ReadFile.c ReadFile.h
	cc -c ReadFile.c

WriteFile.o: WriteFile.c WriteFile.h
	cc -c WriteFile.c
