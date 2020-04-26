CFLAGS = -Wall -Wextra -DDEBUG -g -std=c++14

dp: dp.o
	g++ $(CFLAGS) dp.o -o dp

dp.o: dp.cpp
	g++ $(CFLAGS) -c dp.cpp -o dp.o

clean:
	rm -rf *.o
