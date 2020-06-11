#include <iostream>
#include <string>

#include "sql_lex.h"
#include "sql_parse.h"


struct CommandResult
{
	bool success;
	std::string message;
};

struct QueryResult
{
	bool success;
	std::string message;
};


bool running = false;


// processes Zn0wDB command
CommandResult process_command(std::string& command)
{
	CommandResult result = { true, "" };
	
	if (command == "/help")
	{
		// display list of commands
	}
	else if (command == "/exit" || command == "/quit")
	{
		running = false;
	}
	else
	{
		result.success = false;
		result.message = "Unrecognized command";
	}

	return result;
}

// processes SQL query
QueryResult process_query(std::string query)
{
	QueryResult result = { true, "" };

	std::vector<Token> tokens = lex(query);

	ParseResult parse_result = parse(tokens);
	if (parse_result.success == false)
		std::cout << "SQL parse error: " << parse_result.message << std::endl;

	return result;
}


int main()
{
	std::cout << "Zn0wDB command line interface" << std::endl;
	std::cout << "Enter /help to see the list of available commands" << std::endl;

	std::string user_input = "";

	running = true;
	while (running)
	{
		std::cout << "$ ";
		std::getline(std::cin, user_input);

		if (user_input.at(0) == '/')
		{
			CommandResult result = process_command(user_input);
			if (!result.success)
			{
				std::cout << "Command failed to execute: " << result.message << std::endl;
			}
		}
		else
		{
			QueryResult result = process_query(user_input);
			if (!result.success)
			{
				std::cout << "Command failed to execute: " << result.message << std::endl;
			}
		}
	}
	
	return 0;
}