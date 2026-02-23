/*
 * 	Project: msg_tunnel_for_old_j2me_devices
 * 	File: src/sources/network.c
 * 	By: Timuruch (timuruch909@gmail.com)
*/
#include "../headers/network.h"

//private functions initialisator 
void* handle_connections(void* arg);

void socket_init(SOCK_OBJ* obj){
	obj->socket = socket(AF_INET, SOCK_STREAM, 0);

	if (0 > obj->socket) exit(0x99); //socket init failure

	obj->addr.sin_family = AF_INET;
	obj->addr.sin_port = htons(obj->port); //dont forget to change to obj->port
	if (obj->ip == 0)
		obj->addr.sin_addr.s_addr = INADDR_ANY;
	else
		obj->addr.sin_addr.s_addr = inet_addr(obj->ip); //dont forget to change to obj->ip
	
	obj->addrlen = sizeof(obj->addr);

	if (0 > bind(obj->socket, (struct sockaddr*)&obj->addr, obj->addrlen)) { //bind init failure
		perror("Bind init fialure: ");
		abort();
	}
}

void init_cl_list(SOCK_OBJ* obj) {
	listen(obj->socket, SOMAXCONN);

	if (obj->handler_func == NULL) {
		perror("0x20 No handler func provided!"); //no handler func provided
		abort();
	}

	obj->run = 1;
	pthread_create(&obj->listen_thr, NULL, handle_connections, obj);
}

void stop_all(SOCK_OBJ* obj) {
	obj->run = 0;
	pthread_join(obj->listen_thr, NULL);
	close(obj->socket);
}

void* handle_connections(void* arg) {
	SOCK_OBJ* obj = (SOCK_OBJ*)arg;
	int tries = 0;
	while (obj->run) {
		CL_OBJ* new_client = malloc(sizeof(CL_OBJ));
		if (!new_client) continue;
		
		printf("Waiting for client\n");
		new_client->addrlen = sizeof(new_client->addr);

		new_client->socket = accept(obj->socket, 
				(struct sockaddr*)&new_client->addr, 
				&new_client->addrlen);

		if (new_client->socket < 0 && tries == 2){
			tries++;
			free(new_client);
			if (tries == 2) break;
			continue;
		}

		tries = 0;

		new_client->is_running = 1;

		if (obj->handler_func) pthread_create(&new_client->client_thread, NULL, obj->handler_func, new_client);
	}
	if (tries == 2) exit(0x10); //handle_connections failure
}

void send_text(CL_OBJ* client, char* text) {
	send(client->socket, text, strlen(text), 0);
}
