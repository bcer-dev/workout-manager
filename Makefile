CC=g++

build: src/main.cpp
	$(CC) $^ -c
	$(CC) src/Workout.cpp -c
	$(CC) main.o Workout.o -o bin/wktmgr
	rm *.o

clean:
	rm *.o