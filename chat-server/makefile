./bin/chat-server: ./obj/chat-server.o ./obj/clientHandling.o ./obj/clientLList.o ./obj/serverSetup.o
	cc ./obj/chat-server.o ./obj/clientHandling.o ./obj/clientLList.o ./obj/serverSetup.o -o ./bin/chat-server -lpthread

./obj/chat-server.o : ./src/chat-server.c ./inc/chat-server.h ./inc/clientLList.h
	cc -c ./src/chat-server.c -o ./obj/chat-server.o

./obj/clientHandling.o : ./src/clientHandling.c ./inc/chat-server.h ./inc/clientLList.h
	cc -c ./src/clientHandling.c -o ./obj/clientHandling.o

./obj/serverSetup.o : ./src/serverSetup.c ./inc/chat-server.h ./inc/clientLList.h
	cc -c ./src/serverSetup.c -o ./obj/serverSetup.o

./obj/clientLList.o : ./src/clientLList.c ./inc/clientLList.h
	cc -c ./src/clientLList.c -o ./obj/clientLList.o



all : ./bin/chat-server

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~



