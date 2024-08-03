OBJS = main.o ./AES.o 

server: 
	gcc server.c ./AES/AES.c -o server

client:
	gcc client.c ./AES/AES.c -o client

clean:
	@if [ -f ./server ]; then \
		rm ./server; \
	fi
	
	@if [ -f ./client ]; then \
		rm ./client; \
	fi

	