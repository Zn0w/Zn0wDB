#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "communication.h"


bool client_running = false;


void startServer(int port)
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::acceptor acceptor(
		ioService,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), port)
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
			std::string message = listenToMessage(&clientSocket, errorCode);

			std::cout << "A message from the client: " << message << std::endl;

			std::string msg = "ok";
			if (message == "bye")
				break;
			else
				sendMessage(&clientSocket, msg, errorCode);

			client_running = false;
		}

		clientSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorCode);
		clientSocket.close();
	}
}