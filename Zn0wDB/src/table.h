#pragma once

#include <string>
#include <vector>
#include <stdint.h>


enum DataType
{
	
};

struct Column
{
	DataType data_type;
	std::string name;
	uint16_t properties;	// flags
};

struct Row
{
	DataType data_type;
	void* value;
};

struct Table
{
	std::string name;
	std::vector<Column> columns;
	std::vector<Row> rows;
};