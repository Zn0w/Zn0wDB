#pragma once

#include <string>
#include <vector>

#include "table.h"


struct Database
{
	std::string name;
	std::vector<Table> tables;
};