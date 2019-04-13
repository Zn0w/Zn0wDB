#include <thread>

#include "net/server.h"
#include "net/client.h"

#include "utils/file_io.h"
#include <iostream>


int main()
{
	//std::thread serverThread(startServer, 3457);
	//std::thread clientThread1(startClient, "localhost", "3457");

	//serverThread.join();

	std::vector<std::string> file_contents = read_file("src/main.cpp");
	for (std::string line : file_contents)
		std::cout << line << std::endl;

	write_file("test/test_file.zn0w_sch", "Hello World\n", false);
	write_file("test/test_file.zn0w_sch", "Hello World", true);

	system("pause");

	return 0;
}