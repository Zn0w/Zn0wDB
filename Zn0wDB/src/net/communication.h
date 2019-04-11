#pragma once

#include <string>

#include <boost/asio.hpp>

std::string listenToMessage(boost::asio::ip::tcp::socket* socket, boost::system::error_code errorCode)
{
	char inputBuffer[256];
	std::size_t inputSize = socket->read_some(boost::asio::buffer(inputBuffer), errorCode);
	std::string message(inputBuffer, inputBuffer + inputSize);

	return message;
}

void sendMessage(boost::asio::ip::tcp::socket* socket, std::string message, boost::system::error_code errorCode)
{
	boost::asio::write(socket, boost::asio::buffer(message), errorCode);
}