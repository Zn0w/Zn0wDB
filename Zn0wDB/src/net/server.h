#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "communication.h"

//int port = 3457;
bool client_running = false;

void startServer()
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::acceptor acceptor(
		ioService,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), 3457)
	);

	std::cout << "The server has booted" << std::endl;
	
	while (true)
	{
		boost::system::error_code errorCode;

		boost::asio::ip::tcp::socket clientSocket(ioService);
		acceptor.accept(clientSocket);
		
		client_running = true;

		while (client_running)
		{
			/*char inputBuffer[256];
			std::size_t inputSize = clientSocket.read_some(boost::asio::buffer(inputBuffer), errorCode);
			std::string message(inputBuffer, inputBuffer + inputSize);*/
			std::string message = listenToMessage(&clientSocket, errorCode);

			std::cout << "A message from the client: " << message << std::endl;

			std::string msg = "ok";
			if (message == "bye")
				break;
			else
				//boost::asio::write(clientSocket, boost::asio::buffer(msg), errorCode);
				sendMessage(&clientSocket, msg, errorCode);

			client_running = false;
		}

		clientSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorCode);
		clientSocket.close();
	}
}