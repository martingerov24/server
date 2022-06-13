#include <stdio.h>
#include "Server.h"
int main()
{
	Server server;
	server.bind("tcp://127.0.0.1:5555");
	server.listen();
	return 0;
}

