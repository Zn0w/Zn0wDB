#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

//int port = 3457;

void startServer()
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::acceptor acceptor(
	ioService,
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), 3457)
	);
	
	while (true)
	{
		std::cout << "The server has booted" << std::endl;
		
		boost::system::error_code errorCode;
		
		boost::asio::ip::tcp::socket clientSocket(ioService);
		acceptor.accept(clientSocket);
		
		char inputBuffer[256];
		std::size_t inputSize = clientSocket.read_some(boost::asio::buffer(inputBuffer), errorCode);
		std::string message(inputBuffer, inputBuffer + inputSize);
		
		std::cout << "A message from the client: " << message << std::endl;
		
		clientSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorCode);
		clientSocket.close();
	}
}