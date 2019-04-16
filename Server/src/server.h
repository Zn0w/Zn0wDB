#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>


bool client_running = false;


/*void getFileLength(const char* filepath)
{
	FILE* file = fopen(filepath, "rt");		
	if (file)
	{
		fseek(file, 0, SEEK_END);
		unsigned int length = ftell(file);
		char* data = (char*)malloc(length + 1);
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, sizeof(char), length, file);
		fclose(file);
	}
	else
		sendMessage(&socket, "file_load_fail", errorCode);
}*/

void startServer(int port)
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::acceptor acceptor(
		ioService,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), port)
	);

	std::cout << "The server has booted" << std::endl;
	
	//while (true)
	//{
		boost::system::error_code errorCode;

		boost::asio::ip::tcp::socket clientSocket(ioService);
		acceptor.accept(clientSocket);
		
		FILE* file = fopen("test.txt", "rt");
		if (file)
		{
			fseek(file, 0, SEEK_END);
			unsigned int length = ftell(file);
			char* data = (char*)malloc(length + 1);
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, sizeof(char), length, file);
			fclose(file);

			std::string file_contents(data);

			boost::asio::write(clientSocket, boost::asio::buffer(file_contents), errorCode);
		}
		else
			boost::asio::write(clientSocket, boost::asio::buffer("file_load_fail"), errorCode);

		clientSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorCode);
		clientSocket.close();
	//}
}