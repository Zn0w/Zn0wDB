#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

bool running = false;


void startClient(const char* ip, const char* port)
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::resolver resolver(ioService);
	boost::asio::ip::tcp::resolver::query query(ip, port);
	boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

	boost::asio::ip::tcp::socket socket(ioService);
	boost::asio::connect(socket, endpointIterator);

	boost::system::error_code errorCode;

	running = true;

	std::cout << "The client has booted" << std::endl;

	std::string clientMessage = "load_file";
	boost::asio::write(socket, boost::asio::buffer(clientMessage), errorCode);

	char inputBuffer[256];
	std::size_t inputSize;
	while (running)
	{
		inputSize = socket.read_some(boost::asio::buffer(inputBuffer), errorCode);
		if (inputSize)
		{
			std::string serverMessage(inputBuffer, inputBuffer + inputSize);

			std::cout << serverMessage;

			if (strcmp(serverMessage.c_str(), "file_load_success") == 0)
			{
				//boost::asio::write(socket, boost::asio::buffer("good job!"), errorCode);
				boost::asio::write(socket, boost::asio::buffer("disconnect"), errorCode);
				running = false;
			}
			else if (strcmp(serverMessage.c_str(), "file_load_fail") == 0)
			{
				//boost::asio::write(socket, boost::asio::buffer("that sucks..."), errorCode);
				boost::asio::write(socket, boost::asio::buffer("disconnect"), errorCode);
				running = false;
			}
		}
	}
}