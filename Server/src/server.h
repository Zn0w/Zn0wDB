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

			if (length / 1024 > 1.0f)
				for (int i = 0; i < length / 1024 + 1; i++)
				{
					//char* old_data_ptr = data;
					//std::cout << length - 1024 * i << "  " << i << std::endl;
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
					//std::cout << packet << std::endl;
					//std::string message("\npacket sent\n");
					//boost::asio::write(clientSocket, boost::asio::buffer(message), errorCode);

					//free(old_data_ptr);
				}
			else
			{
				std::string file_contents(data);
				boost::asio::write(clientSocket, boost::asio::buffer(file_contents), errorCode);
				//free(data);
			}
		}
		else
			boost::asio::write(clientSocket, boost::asio::buffer("file_load_fail"), errorCode);

		clientSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorCode);
		clientSocket.close();
	//}
}