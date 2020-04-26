CFLAGS = -Wall -Wextra -DDEBUG -g -std=c++14

divAndConq: divAndConq.o divAndConq.cpp
	g++ $(CFLAGS) divAndConq.o -o divAndConq

divAndConq.o: divAndConq.cpp
	g++ $(CFLAGS) -c divAndConq.cpp -o divAndConq.o

dp: dp.o dp.cpp
	g++ $(CFLAGS) dp.o -o dp

dp.o: dp.cpp
	g++ $(CFLAGS) -c dp.cpp -o dp.o

inputgenerator: inputgenerator.o inputgenerator.cpp
	g++ $(CFLAGS) inputgenerator.o -o inputgenerator

inputgenerator.o: inputgenerator.cpp
	g++ $(CFLAGS) -c inputgenerator.cpp -o inputgenerator.o

clean:
	rm -rf ./divAndConq ./dp ./inputgenerator output.txt *.o
