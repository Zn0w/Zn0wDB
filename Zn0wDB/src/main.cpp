#include <thread>

#include "net/server.h"
#include "net/client.h"

int main()
{
	std::thread serverThread(startServer);
	std::thread clientThread1(startClient);
	std::thread clientThread2(startClient);

	serverThread.join();

	return 0;
}