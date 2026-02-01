#include "./headers/network.h"

void handle_clients(CL_OBJ* client);

int main() {
	SOCK_OBJ server = { 0 };
	
	char* ip = "127.0.0.1";

	server.ip = ip;
	server.port = 8080;
	
	server.handler_func = handle_clients;	

	printf("Initing socket...\n");
	socket_init(&server);
	
	printf("I think i am ready\n");	
	init_cl_list(&server);

	while (1) {
		continue;
	}
}

void handle_clients(CL_OBJ* client) {
	printf("Client Connected!\n");
	close(client->socket);
	free(client);
}
