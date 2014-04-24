all: da

da: Main.cpp
	g++-4.7 -std=c++11 Main.cpp -o da

clean:
	rm *.o *.gch da
