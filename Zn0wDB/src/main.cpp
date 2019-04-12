#include <thread>

#include "net/server.h"
#include "net/client.h"

#include "utils/file_io.h"

int main()
{
	//std::thread serverThread(startServer, 3457);
	//std::thread clientThread1(startClient, "localhost", "3457");

	//serverThread.join();

	read_file("src/main.cpp");

	system("pause");

	return 0;
}