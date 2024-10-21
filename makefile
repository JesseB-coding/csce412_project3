CC = g++
CFLAGS = -Wall -Werror

all: myprogram

myprogram: main.o webserver.o loadbalancer.o request.o
	$(CC) $(CFLAGS) -o myprogram main.o webserver.o loadbalancer.o request.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

webserver.o: webserver.cpp webserver.h request.h
	$(CC) $(CFLAGS) -c webserver.cpp

loadbalancer.o: loadbalancer.cpp loadbalancer.h webserver.h request.h
	$(CC) $(CFLAGS) -c loadbalancer.cpp

request.o: request.cpp request.h
	$(CC) $(CFLAGS) -c request.cpp

clean:
	rm -f myprogram *.o