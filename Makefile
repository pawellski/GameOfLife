a.out: main.o Game.o ReadFile.o WriteFile.o
	cc main.o Game.o ReadFile.o WriteFile.o

main.o: main.c Struct.h Game.h ReadFile.h
	cc -c main.c
	
Game.o: Game.c Game.h WriteFile.h Struct.h
	cc -c Game.c

ReadFile.o: ReadFile.c ReadFile.h Struct.h
	cc -c ReadFile.c

WriteFile.o: WriteFile.c WriteFile.h Struct.h
	cc -c WriteFile.c