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
		result = { false, "create database statement must be supplied with a database name" };
}

void parse_create_table_statement(ParseResult& result, std::vector<Token>& tokens)
{
	if (tokens.at(tokens.size() - 1).type != TABLE_NAME)
		result = { false, "create table statement must be supplied with a table name" };
}

void parse_describe_statement(ParseResult& result, std::vector<Token>& tokens)
{
	if (tokens.at(tokens.size() - 1).type != TABLE_NAME)
		result = { false, "describe statement must be supplied with a table name" };
}

void parse_select_statement(ParseResult& result, std::vector<Token>& tokens)
{
	bool columns_found = false;
	bool table_name_found = false;
	for (Token token : tokens)
	{
		if (!table_name_found && !columns_found && token.type == COLUMN_NAME)
			columns_found = true;
		else if (columns_found && !table_name_found && token.type == TABLE_NAME)
			table_name_found = true;
		else if (token.type != WHERE_CLAUSE)
		{
			columns_found = false;
			table_name_found = false;
		}
	}

	if (!columns_found && ! table_name_found)
		result = { false, "invalid select statement" };
	else if (!columns_found)
		result = { false, "select statement requires for columns to be specified" };
	else if (!table_name_found)
		result = { false, "select statement requires for table name to be specified" };
}

void parse_insert_statement(ParseResult& result, std::vector<Token>& tokens)
{
	
}

void parse_delete_statement(ParseResult& result, std::vector<Token>& tokens)
{
	
}

void parse_unrecognized_statement(ParseResult& result, std::vector<Token>& tokens)
{
	result = { false, "failed to recognize this statement" };
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

		case UNRECOGNIZED:
		{
			parse_unrecognized_statement(result, tokens);
		} break;
	}

	return result;
}