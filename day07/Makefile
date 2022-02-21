all: day07.o IntCode.o
	g++ -o  day07 day07.o IntCode.o -std=c++17 

day07.o: day07.cpp
	g++ -c  day07.cpp -I ./ -std=c++17

IntCode.o: ../int_code/IntCode.cpp
	g++ -c  ../int_code/IntCode.cpp -I ./ -std=c++17