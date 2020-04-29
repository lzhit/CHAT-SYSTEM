./bin/chat-client: ./obj/chat-client.o ./obj/serverConnection.o ./obj/ncursesUI.o ./obj/inputHandling.o ./obj/outputHandling.o 
	cc ./obj/chat-client.o ./obj/serverConnection.o ./obj/ncursesUI.o ./obj/inputHandling.o ./obj/outputHandling.o -lncurses -o ./bin/chat-client -lpthread

./obj/chat-client.o : ./src/chat-client.c ./inc/chat-client.h ./inc/ncursesUI.h
	cc -c ./src/chat-client.c -o ./obj/chat-client.o

./obj/serverConnection.o : ./src/serverConnection.c ./inc/chat-client.h
	cc -c ./src/serverConnection.c -o ./obj/serverConnection.o

./obj/ncursesUI.o : ./src/ncursesUI.c ./inc/ncursesUI.h
	cc -c ./src/ncursesUI.c -o ./obj/ncursesUI.o

./obj/inputHandling.o : ./src/inputHandling.c ./inc/chat-client.h ./inc/ncursesUI.h
	cc -c ./src/inputHandling.c -o ./obj/inputHandling.o

./obj/outputHandling.o : ./src/outputHandling.c ./inc/chat-client.h ./inc/ncursesUI.h
	cc -c ./src/outputHandling.c -o ./obj/outputHandling.o

all : ./bin/chat-client

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~


