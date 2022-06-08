#include <stdio.h>
#include "Server.h"
int main()
{
	Server server;
	server.bind("tcp://0.0.0.0:5555");
	server.listen();
	return 0;
}

