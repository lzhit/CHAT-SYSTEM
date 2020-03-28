./bin/chat-client: ./obj/chat-client.o
	cc ./obj/chat-client.o -o ./bin/chat-client

./obj/chat-client.o : ./src/chat-client.c ./inc/chat-client.h
	cc -c ./src/chat-client.c -o ./obj/chat-client.o

all : ./bin/chat-client

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~


