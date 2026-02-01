#include "../headers/network.h"

//private functions initialisator 
void* handle_connections(void* arg);
void* test_func(void* arg);

void socket_init(SOCK_OBJ* obj){
	obj->socket = socket(AF_INET, SOCK_STREAM, 0);

	if (!obj->socket) exit(0x99); //socket init failure

	obj->addr.sin_family = AF_INET;
	obj->addr.sin_port = htons(8080); //dont forget to change to obj->port
	obj->addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //dont forget to change to obj->ip

	if (!bind(obj->socket, (struct sockaddr*)&obj->addr, obj->addrlen)) exit(0x98); //bind init failure
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
	
		printf("Si!%d\n", new_client->socket);

		if (new_client->socket < 0 && tries == 2){
			tries++;
			free(new_client);
			if (tries == 2) break;
			continue;
		}

		tries = 0;

		if (obj->handler_func) obj->handler_func(new_client);
	}
	if (tries == 2) exit(0x10); //handle_connections failure
}
