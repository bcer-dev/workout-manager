CC=g++

build: src/main.cpp
	$(CC) $^ -c
	$(CC) src/Workout.cpp -c
	$(CC) src/Date.cpp -c
	$(CC) main.o Workout.o Date.o -o bin/wktmgr
	rm *.o

clean:
	rm *.o