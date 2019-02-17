#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

//const char* ip = "localhost";
//const char* port = "3457";

void startClient()
{
	std::cout << "The client has booted" << std::endl;
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::resolver resolver(ioService);
	boost::asio::ip::tcp::resolver::query query("localhost", "3457");
	boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

	boost::asio::ip::tcp::socket socket(ioService);
	boost::asio::connect(socket, endpointIterator);

	boost::system::error_code errorCode;

	std::string message = "Hi!";
	boost::asio::write(socket, boost::asio::buffer(message), errorCode);
}