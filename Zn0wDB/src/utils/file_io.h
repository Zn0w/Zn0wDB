#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

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

	printf("%s", data);

	return std::vector<std::string>();
}

void write_file(const char* filepath, const char* mode)
{
	
}