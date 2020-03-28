./bin/chat-server: ./obj/chat-server.o
	cc ./obj/chat-server.o -o ./bin/chat-server -lpthread

./obj/chat-server.o : ./src/chat-server.c ./inc/chat-server.h
	cc -c ./src/chat-server.c -o ./obj/chat-server.o

all : ./bin/chat-server

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~



