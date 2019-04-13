#pragma once

#include <vector>

#include "column.h"


struct Table
{
	const char* name;
	std::vector<Column> columns;
};