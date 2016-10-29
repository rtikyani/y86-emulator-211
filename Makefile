all: y86emul
y86emul: src/directives.c src/instructions.c src/y86emul.c
		gcc -lm -Wall -o y86emul src/data.h src/directives.c src/instructions.c src/parse.c src/y86emul.c
clean:
		rm y86emul
