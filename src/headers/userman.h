/*
 * 	Project: msg_tunnel_for_old_j2me_devices
 * 	File: src/headers/userman.h (User Manager)
 * 	By: Timuruch (timuruch909@gmail.com)
 *
 * 	Note: I know that saving users in users.us
 * 	and passwords.ps in raw format is really 
 * 	stupid and insecure... BUT! Since this file
 * 	would be only seen by host (if he would
 * 	explicitly open it) and not by some weirdos
 * 	from the internet (if ofc the server would
 * 	not be hacked by these weridos). So in theory
 * 	the whole data story should be alr.
*/
#include "network.h"

int checkPass(char buffer[256], CL_OBJ* client); //check_password

void regNewClient(); //register new client to the database
