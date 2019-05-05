#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>


namespace zn0w_utils {

#define MINIMUM_STRINGS 4					// corresponds to the schema storing format (see docs) - the required data


std::vector<std::string> read_file(const char* filepath)
{
	FILE* file = fopen(filepath, "rt");		// rt stands for read text
	fseek(file, 0, SEEK_END);
	unsigned int length = ftell(file);		// the amount of passed bytes (the amount of bytes in file)
	char* data = (char*) malloc(length + 1);// +1 for termination character
	memset(data, 0, length + 1);			// set's the length+1 bytes of the data to 0
	fseek(file, 0, SEEK_SET);				// go to the beggining of the file
	fread(data, sizeof(char), length, file);
	fclose(file);

	std::stringstream file_data(data);
	std::string line;
	std::vector<std::string> result;
	result.reserve(MINIMUM_STRINGS);
	while (std::getline(file_data, line, '\n'))
	{
		result.push_back(line);
	}

	return result;
}

void write_file(const char* filepath, const char* data, bool append)
{
	FILE* file;
	
	if (append)
		file = fopen(filepath, "a");
	else
		file = fopen(filepath, "w");

	if (file)
		fprintf(file, data);
	else
		printf("Failed to write file %s\n", filepath);
	
	fclose(file);
}

}