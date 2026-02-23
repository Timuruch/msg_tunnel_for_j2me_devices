#include "../headers/comman.h"

void com_handler(CL_OBJ* client){
	char buffer[256] = { 0 };
	while (1) {
		int recieved = recv(client->socket, buffer, sizeof(buffer), 0);
		if (buffer == 0) break;

		buffer[recieved] = '\0';

		if (buffer[0] == 'l') { //login
			if (!checkPass(buffer, client)) break;
		}else if (buffer[0] == 'r') { //register 
			regNewClient();
		}

		if (!client->is_running) break;
	}
	client->is_running = 0;
}
