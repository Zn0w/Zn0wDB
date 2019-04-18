// Right now the server only works with one client at a time

#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>


bool server_running = false;
bool client_running = false;


void startServer(int port)
{
	boost::asio::io_service ioService;
	boost::asio::ip::tcp::acceptor acceptor(
		ioService,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), port)
	);

	server_running = true;

	std::cout << "The server has booted" << std::endl;
	
	while (server_running)
	{
		boost::system::error_code errorCode;

		boost::asio::ip::tcp::socket clientSocket(ioService);
		acceptor.accept(clientSocket);

		client_running = true;

		std::cout << "The client has connected" << std::endl;

		char inputBuffer[256];
		std::size_t inputSize;
		while (client_running)
		{
			inputSize = clientSocket.read_some(boost::asio::buffer(inputBuffer), errorCode);
			if (inputSize)
			{
				std::string message(inputBuffer, inputBuffer + inputSize);

				std::cout << message << std::endl;

				if (strcmp(message.c_str(), "load_file") == 0)
				{
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

						char* old_data_ptr = data;

						if (length / 1024 > 1.0f)
							for (int i = 0; i < length / 1024 + 1; i++)
							{
								if (length - 1024 * i < 1024)
								{
									data = data + 1024;
									unsigned short leftover = length - 1024 * i;
									std::string packet(data, leftover);
									boost::asio::write(clientSocket, boost::asio::buffer(packet), errorCode);
									continue;
								}
								else if (length - 1024 * i == 0)
									break;

								if (i > 0)
									data = data + 1024;
								std::string packet(data, 1024);
								boost::asio::write(clientSocket, boost::asio::buffer(packet), errorCode);
							}
						else
						{
							std::string file_contents(data);
							boost::asio::write(clientSocket, boost::asio::buffer(file_contents), errorCode);
						}

						free(old_data_ptr);

						boost::asio::write(clientSocket, boost::asio::buffer("file_load_success"), errorCode);
					}
					else
						boost::asio::write(clientSocket, boost::asio::buffer("file_load_fail"), errorCode);
				}

				else if (strcmp(message.c_str(), "disconnect") == 0)
					client_running = false;
			}
		}

		clientSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorCode);
		clientSocket.close();

		std::cout << "The client has disconnected" << std::endl;
	}
}