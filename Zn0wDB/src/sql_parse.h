#pragma once

#include <string>
#include <vector>

#include "sql_lex.h"


struct ParseResult
{
	bool success;
	std::string message;
};


void parse_create_database_statement(ParseResult& result, std::vector<Token>& tokens)
{
	if (tokens.at(tokens.size() - 1).type != DATABASE_NAME)
		result = { false, "create database statement must be supplied with database name" };
	else if (tokens.at(tokens.size() - 1).literal == "")
		result = { false, "create database statement must be supplied with VALID database name" };
}

void parse_create_table_statement(ParseResult& result, std::vector<Token>& tokens)
{
	if (tokens.at(tokens.size() - 1).type != TABLE_NAME)
		result = { false, "create table statement must be supplied with table name" };
	else if (tokens.at(tokens.size() - 1).literal == "")
		result = { false, "create database statement must be supplied with VALID table name" };
}

void parse_describe_statement(ParseResult& result, std::vector<Token>& tokens)
{
	if (tokens.at(tokens.size() - 1).type != TABLE_NAME)
		result = { false, "describe statement must be supplied with table name" };
	else if (tokens.at(tokens.size() - 1).literal == "")
		result = { false, "create database statement must be supplied with VALID table name" };
}

void parse_select_statement(ParseResult& result, std::vector<Token>& tokens)
{
	int i = 1;
	//if (tokens.at(i).type == COLUMN_NAME)
}

void parse_insert_statement(ParseResult& result, std::vector<Token>& tokens)
{
	
}

void parse_delete_statement(ParseResult& result, std::vector<Token>& tokens)
{
	
}

ParseResult parse(std::vector<Token>& tokens)
{
	ParseResult result = { true, "" };

	Token token = tokens.at(0);
	
	switch (token.type)
	{
		case CREATE_DATABASE_STATEMENT :
		{
			parse_create_database_statement(result, tokens);
		} break;

		case CREATE_TABLE_STATEMENT:
		{
			parse_create_table_statement(result, tokens);
		} break;

		case DESCRIBE_STATEMENT:
		{
			parse_describe_statement(result, tokens);
		} break;

		case SELECT_STATEMENT:
		{
			parse_select_statement(result, tokens);
		} break;

		case INSERT_STATEMENT:
		{
			parse_insert_statement(result, tokens);
		} break;

		case DELETE_STATEMENT:
		{
			parse_delete_statement(result, tokens);
		} break;
	}

	return result;
}