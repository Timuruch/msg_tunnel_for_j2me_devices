/*
 * 	Project: msg_tunnel_for_old_j2me_devices
 *	File: src/main.c
 *	By: Timuruch (timuruch909@gmail.com)
 *
*/
#include "./headers/comman.h"
//#include "./headers/network.h"

void* handle_clients(void* arg);

int main() {
	SOCK_OBJ server = { 0 };
	
	char* ip = "127.0.0.1";

	server.ip = ip; //if the server.ip = 0, the server is gonna use INADDR_ANY
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
	while (client->is_running) {
		com_handler(client);
	}

	printf("Closing connection!\n");

	close(client->socket);
	free(client);
}
