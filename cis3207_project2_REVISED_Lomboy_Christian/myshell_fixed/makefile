HEADERS = commands.h util.h internals.h

output: main.o commands.o util.o internals.o exec.o $(HEADERS)
	gcc main.o commands.o util.o internals.o exec.o -o myshell

main.o: main.c
	gcc -c main.c

commands.o: commands.c commands.h
	gcc -c commands.c

util.o: util.c util.h
	gcc -c util.c

internals.o: internals.c internals.h
	gcc -c internals.c

exec.o: exec.c exec.h
	gcc -c exec.c

clean:
	rm *.o myshell
