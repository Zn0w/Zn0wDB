#pragma once

#include <vector>


enum DataType		// will be appended
{
	INT,
	TINYINT,
	BIGINT,
	DATETIME,
	CHAR,
	VARCHAR,
	TEXT
};

enum Attribute		// will be appended
{
	NOTNULL
};

struct Column
{
	const char* name;
	DataType type;
	std::vector<Attribute> attributes;
};