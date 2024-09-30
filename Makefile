all:
	gcc *.c -o optichess -Wall -Wextra -pedantic

clean:
	rm -rf optichess && clear

run:
	./optichess
