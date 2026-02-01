#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct CL_OBJ {
	int socket;
	struct sockaddr_in addr;
	socklen_t addrlen;
} CL_OBJ;

typedef struct SOCK_OBJ {
	int socket;
	struct sockaddr_in addr;

	socklen_t addrlen;

	char* ip;
	int port;

	int run; //flag whether socket is active (after listen, before close)

	pthread_t listen_thr; //thread used for listening for new clients	
	void (*handler_func)(CL_OBJ*); //handler_function (will be called after client connects)
} SOCK_OBJ;

void socket_init(SOCK_OBJ* obj);

void init_cl_list(SOCK_OBJ* obj);

void stop_all(SOCK_OBJ* obj);
