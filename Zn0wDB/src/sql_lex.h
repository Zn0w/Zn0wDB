#pragma once

#include <string>
#include <vector>


enum TokenType
{
	CREATE_DATABASE_STATEMENT,
	CREATE_TABLE_STATEMENT,
	DESCRIBE_STATEMENT,	// shows the structure of the table (its columns)
	SELECT_STATEMENT,
	INSERT_STATEMENT,
	DELETE_STATEMENT
};

struct Token
{
	TokenType type;
	std::string literal;
};


std::vector<Token> lex(std::string& query)
{
	std::vector<Token> tokens;
	
	char word[256] = "";
	int c_i = 0, i = 0;
	int query_length = query.length();
	while (c_i < query_length)
	{
		if (query.at(i) == ' ' || query.at(i) == '\n' || query.at(i) == '\t')
		{
			if (strcmp(word, "select") == 0)
				tokens.push_back();
		}
	}
}