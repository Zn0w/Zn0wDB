#pragma once

#include <vector>

#include "table.h"


struct Schema
{
	const char* name;
	const char* authorization;
	const char* char_set;
	const char* path;
	std::vector<Table> tables;
};

Schema* create_schema(
	const char* s_name, 
	const char* s_authorization, 
	const char* s_char_set, 
	const char* s_path,
	std::vector<Table> s_tables
)
{
	Schema* s = (Schema*) malloc(sizeof(Schema));
	s->name = s_name;
	s->authorization = s_authorization;
	s->char_set = s_char_set;
	s->path = s_path;
	s->tables = s_tables;
	return s;
}

void delete_schema(Schema* schema)
{
	free(schema);
};