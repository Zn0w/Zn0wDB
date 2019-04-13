#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>


void startClient(const char* ip, const char* port)
{
	std::cout << "The client has booted" << std::endl;
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::resolver resolver(ioService);
	boost::asio::ip::tcp::resolver::query query(ip, port);
	boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

	boost::asio::ip::tcp::socket socket(ioService);
	boost::asio::connect(socket, endpointIterator);

	boost::system::error_code errorCode;

	std::string clientMessage = "Hi!";
	boost::asio::write(socket, boost::asio::buffer(clientMessage), errorCode);

	while (true)
	{
		char inputBuffer[256];
		std::size_t inputSize = socket.read_some(boost::asio::buffer(inputBuffer), errorCode);
		std::string serverMessage(inputBuffer, inputBuffer + inputSize);

		std::cout << serverMessage << std::endl;

		std::cin >> clientMessage;
		boost::asio::write(socket, boost::asio::buffer(clientMessage), errorCode);
	}
}