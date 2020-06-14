main: main.o models.o utils.o
	g++ -Wall -o main main.o models.o utils.o
utils.o: utils.cpp
	g++ -Wall -c utils.cpp
models.o: models.cpp
	g++ -Wall -c models.cpp
main.o: main.cpp
	g++ -Wall -c main.cpp

clean:
	rm -f *.o main