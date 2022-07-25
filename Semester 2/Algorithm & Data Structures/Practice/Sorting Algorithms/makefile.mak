p1_compile: driver.cpp
	g++ -Wall -o p1 driver.cpp

p1_run: p1
	./p1