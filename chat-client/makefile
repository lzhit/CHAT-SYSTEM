./bin/chat-client: ./obj/chat-client.o ./obj/ncursesUI.o
	cc ./obj/chat-client.o ./obj/ncursesUI.o -lncurses -o ./bin/chat-client -lpthread

./obj/chat-client.o : ./src/chat-client.c ./inc/chat-client.h ./inc/ncursesUI.h
	cc -c ./src/chat-client.c -o ./obj/chat-client.o

./obj/ncursesUI.o : ./src/ncursesUI.c ./inc/ncursesUI.h
	cc -c ./src/ncursesUI.c -o ./obj/ncursesUI.o

all : ./bin/chat-client

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~


