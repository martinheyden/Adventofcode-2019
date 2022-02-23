all: day09.o IntCode.o
	g++ -o  day09 day09.o IntCode.o -std=c++17 

day09.o: day09.cpp
	g++ -c  day09.cpp -I ./ -std=c++17

IntCode.o: ../int_code/IntCode.cpp
	g++ -c  ../int_code/IntCode.cpp -I ./ -std=c++17