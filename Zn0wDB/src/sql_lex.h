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
	DELETE_STATEMENT,
	UPDATE_STATEMENT,
	DATABASE_NAME,
	TABLE_NAME,
	WHERE_CLAUSE,
	COLUMN_NAME,
	VALUE,
	UNRECOGNIZED
};

struct Token
{
	TokenType type;
	std::string literal;
};


std::vector<Token> lex(std::string& query)
{
	std::vector<Token> tokens;
	
	char* query_cp = &query[0];
	char* word = 0;
	word = strtok(query_cp, " ()\n\t;");
	while (word)
	{
		if (strcmp(word, "create") == 0)
		{
			word = strtok(0, " ()\n\t;");
			if (strcmp(word, "database") == 0)
			{
				tokens.push_back({ CREATE_DATABASE_STATEMENT, "" });
				word = strtok(0, " ()\n\t;");
				tokens.push_back({ DATABASE_NAME, word });
			}
			else if (strcmp(word, "table") == 0)
			{
				tokens.push_back({ CREATE_TABLE_STATEMENT, "" });
				word = strtok(0, " ()\n\t;");
				tokens.push_back({ TABLE_NAME, word });
			}
			else
				tokens.push_back({ UNRECOGNIZED, word });
		}
		else if (strcmp(word, "describe") == 0)
		{
			tokens.push_back({	DESCRIBE_STATEMENT, "" });
			word = strtok(0, " ()\n\t;");
			tokens.push_back({ TABLE_NAME, word });
		}
		else if (strcmp(word, "select") == 0)
		{
			tokens.push_back({ SELECT_STATEMENT, "" });
			word = strtok(0, " ()\n\t;");
			while (word && strcmp(word, "from") != 0)
			{
				tokens.push_back({ COLUMN_NAME, word });
				word = strtok(0, " ()\n\t;");
			}
			word = strtok(0, " ()\n\t;");
			tokens.push_back({ TABLE_NAME, word });

			word = strtok(0, " ()\n\t;");
			if (word != 0 && strcmp(word, "where") == 0)
			{
				word = strtok(0, " ");
				tokens.push_back({ WHERE_CLAUSE, word });
			}
		}
		else if (strcmp(word, "insert") == 0)
		{
			tokens.push_back({ INSERT_STATEMENT, "" });
			
			word = strtok(0, " ()\n\t;");
			if (strcmp(word, "into") != 0)
			{
				tokens.push_back({ UNRECOGNIZED, word });
				continue;
			}

			word = strtok(0, " ()\n\t;");
			tokens.push_back({ TABLE_NAME, word });

			word = strtok(0, " ()\n\t;,");
			while (word && strcmp(word, "values") != 0)
			{
				tokens.push_back({ COLUMN_NAME, word });
				word = strtok(0, " ()\n\t;");
			}

			word = strtok(0, " ()\n\t;,\'");
			while (word)
			{
				tokens.push_back({ VALUE, word });
				word = strtok(0, " ()\n\t;");
			}
		}
		else
		{
			tokens.push_back({ UNRECOGNIZED, word });
		}

		word = strtok(0, " ()\n\t;");
	}
}