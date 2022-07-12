CC=g++

build: src/main.cpp
	$(CC) $^ -o bin/workoutmgr