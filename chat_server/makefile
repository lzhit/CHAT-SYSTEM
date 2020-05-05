./bin/chat_server: ./obj/chat_server.o ./obj/client_manager.o ./obj/client_linked_list.o ./obj/server_setup.o
	cc ./obj/chat_server.o ./obj/client_manager.o ./obj/client_linked_list.o ./obj/server_setup.o -o ./bin/chat_server -lpthread

./obj/chat_server.o : ./src/chat_server.c ./inc/chat_server.h ./inc/client_linked_list.h
	cc -c ./src/chat_server.c -o ./obj/chat_server.o

./obj/client_manager.o : ./src/client_manager.c ./inc/chat_server.h ./inc/client_linked_list.h
	cc -c ./src/client_manager.c -o ./obj/client_manager.o

./obj/server_setup.o : ./src/server_setup.c ./inc/chat_server.h ./inc/client_linked_list.h
	cc -c ./src/server_setup.c -o ./obj/server_setup.o

./obj/client_linked_list.o : ./src/client_linked_list.c ./inc/client_linked_list.h
	cc -c ./src/client_linked_list.c -o ./obj/client_linked_list.o



all : ./bin/chat_server

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~



