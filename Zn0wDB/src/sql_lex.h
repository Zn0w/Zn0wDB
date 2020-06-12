#pragma once

#include <string>
#include <vector>


const char* reserved_words[] = {
	"create", "database", "table", "describe", "select", "insert", "delete", "update", "drop", "alter", "where",
	"from", "set", "into"
};

enum TokenType
{
	CREATE_DATABASE_STATEMENT,
	CREATE_TABLE_STATEMENT,
	DESCRIBE_STATEMENT,	// shows the structure of the table (its columns)
	SELECT_STATEMENT,
	INSERT_STATEMENT,
	DELETE_STATEMENT,
	UPDATE_STATEMENT,
	DROP_STATEMENT,
	ALTER_STATEMENT,

	DATABASE_NAME,
	TABLE_NAME,
	WHERE_CLAUSE,
	COLUMN_NAME,
	COLUMN_TYPE,
	VALUE,
	
	UNRECOGNIZED
};

struct Token
{
	TokenType type;
	std::string literal;
};


bool is_reserved_word(const char* literal)
{
	int reserved_words_count = sizeof(reserved_words) / sizeof(char*);
	
	for (int i = 0; i < reserved_words_count; i++)
		if (strcmp(literal, reserved_words[i]) == 0)
			return true;
	return false;
}

void add_new_token(std::vector<Token>& tokens, TokenType type, const char* literal)
{
	if (literal == 0)
		tokens.push_back({ UNRECOGNIZED, "" });
	else if (is_reserved_word(literal))
		tokens.push_back({ UNRECOGNIZED, "" });	// NOTE: maybe there will be a special token type
	else
		tokens.push_back({ type, literal });
}

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
				add_new_token(tokens, CREATE_DATABASE_STATEMENT, "");
				word = strtok(0, " ()\n\t;");
				add_new_token(tokens, DATABASE_NAME, word);
			}
			else if (strcmp(word, "table") == 0)
			{
				add_new_token(tokens, CREATE_TABLE_STATEMENT, "");
				word = strtok(0, " ()\n\t;");
				add_new_token(tokens, TABLE_NAME, word);

				word = strtok(0, " ()\n\t,");
				while (word != 0 && strcmp(word, ";") != 0)
				{
					add_new_token(tokens, COLUMN_NAME, word);
					word = strtok(0, " ()\n\t,");
					add_new_token(tokens, COLUMN_TYPE, word);
					word = strtok(0, " ()\n\t,");
				}
			}
			else
				add_new_token(tokens, UNRECOGNIZED, word);
		}
		else if (strcmp(word, "describe") == 0)
		{
			add_new_token(tokens, DESCRIBE_STATEMENT, "");
			word = strtok(0, " ()\n\t;");
			add_new_token(tokens, TABLE_NAME, word);
		}
		else if (strcmp(word, "select") == 0)
		{
			add_new_token(tokens, SELECT_STATEMENT, "");
			word = strtok(0, " ()\n\t;");
			while (word && strcmp(word, "from") != 0)
			{
				add_new_token(tokens, COLUMN_NAME, word);
				word = strtok(0, " ()\n\t;");
			}
			word = strtok(0, " ()\n\t;");
			add_new_token(tokens, TABLE_NAME, word);

			word = strtok(0, " ()\n\t;");
			if (word != 0 && strcmp(word, "where") == 0)
			{
				word = strtok(0, " ");
				add_new_token(tokens, WHERE_CLAUSE, word);
			}
		}
		else if (strcmp(word, "insert") == 0)
		{
			add_new_token(tokens, INSERT_STATEMENT, "");
			
			word = strtok(0, " ()\n\t;");
			if (strcmp(word, "into") != 0)
			{
				add_new_token(tokens, UNRECOGNIZED, word);
				continue;
			}

			word = strtok(0, " ()\n\t;");
			add_new_token(tokens, TABLE_NAME, word);

			word = strtok(0, " ()\n\t;,");
			while (word && strcmp(word, "values") != 0)
			{
				add_new_token(tokens, COLUMN_NAME, word);
				word = strtok(0, " ()\n\t;,");
			}

			word = strtok(0, " ()\n\t;,\'");
			while (word)
			{
				add_new_token(tokens, VALUE, word);
				word = strtok(0, " ()\n\t;,\'");
			}
		}
		else if (strcmp(word, "delete") == 0)
		{
			add_new_token(tokens, DELETE_STATEMENT, "");
			
			word = strtok(0, " ()\n\t;");
			if (strcmp(word, "from") != 0)
			{
				add_new_token(tokens, UNRECOGNIZED, word);
				continue;
			}

			word = strtok(0, " ()\n\t;");
			add_new_token(tokens, TABLE_NAME, word);

			word = strtok(0, " ()\n\t;");
			if (word != 0 && strcmp(word, "where") == 0)
			{
				word = strtok(0, " ");
				add_new_token(tokens, WHERE_CLAUSE, word);
			}
		}
		else if (strcmp(word, "update") == 0)
		{
			add_new_token(tokens, UPDATE_STATEMENT, "");
			
			word = strtok(0, " ()\n\t;");
			add_new_token(tokens, TABLE_NAME, word);

			word = strtok(0, " ()\n\t;");
			if (strcmp(word, "set") != 0)
			{
				add_new_token(tokens, UNRECOGNIZED, word);
				continue;
			}

			word = strtok(0, " ()\n\t;,=");
			while (word && strcmp(word, "where") != 0)
			{
				add_new_token(tokens, COLUMN_NAME, word);
				
				word = strtok(0, " ()\n\t;,=\'");
				add_new_token(tokens, VALUE, word);

				word = strtok(0, " ()\n\t;,\'");
			}

			if (word != 0 && strcmp(word, "where") == 0)
			{
				word = strtok(0, " ");
				add_new_token(tokens, WHERE_CLAUSE, word);
			}
			else
				add_new_token(tokens, UNRECOGNIZED, word);
		}
		else
		{
			add_new_token(tokens, UNRECOGNIZED, word);
		}

		word = strtok(0, " ()\n\t;");
	}

	return tokens;
}