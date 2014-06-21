./main:./myls2.o
	gcc -o main ./myls2.o
./myls2.o:./myls2.c
	gcc -c ./myls2.c -o ./myls2.o
