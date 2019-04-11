#include <thread>

#include "net/server.h"
#include "net/client.h"

int main()
{
	std::thread serverThread(startServer, 3457);
	std::thread clientThread1(startClient, "localhost", "3457");

	serverThread.join();

	return 0;
}