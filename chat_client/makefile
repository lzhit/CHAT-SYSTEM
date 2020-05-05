./bin/chat_client: ./obj/chat_client.o ./obj/connection_manager.o ./obj/ncurses_UI.o ./obj/input_manager.o ./obj/output_manager.o 
	cc ./obj/chat_client.o ./obj/connection_manager.o ./obj/ncurses_UI.o ./obj/input_manager.o ./obj/output_manager.o -lncurses -o ./bin/chat_client -lpthread

./obj/chat_client.o : ./src/chat_client.c ./inc/chat_client.h ./inc/ncurses_UI.h
	cc -c ./src/chat_client.c -o ./obj/chat_client.o

./obj/connection_manager.o : ./src/connection_manager.c ./inc/chat_client.h
	cc -c ./src/connection_manager.c -o ./obj/connection_manager.o

./obj/ncurses_UI.o : ./src/ncurses_UI.c ./inc/ncurses_UI.h
	cc -c ./src/ncurses_UI.c -o ./obj/ncurses_UI.o

./obj/input_manager.o : ./src/input_manager.c ./inc/chat_client.h ./inc/ncurses_UI.h
	cc -c ./src/input_manager.c -o ./obj/input_manager.o

./obj/output_manager.o : ./src/output_manager.c ./inc/chat_client.h ./inc/ncurses_UI.h
	cc -c ./src/output_manager.c -o ./obj/output_manager.o

all : ./bin/chat_client

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~


