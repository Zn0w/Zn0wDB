#include <iostream>
#include <string>

#include "../../Zn0wDB/src/utils/file_io.h"


void create_schema()
{
	std::string schema_data = "";
	const char* filepath = "default/test_schema.zn0w_sch";

	/*schema_data += "TestSchema" + '\n';
	schema_data += "user123" + '\n';
	schema_data += "utf8" + '\n';
	schema_data += "default/data/test_schema_data" + '\n';
	std::cout << schema_data << std::endl;

	zn0w_utils::write_file(filepath, schema_data.c_str(), false);*/
	
	zn0w_utils::write_file(filepath, "TestSchema\n", false);
	zn0w_utils::write_file(filepath, "user123\n", true);
	zn0w_utils::write_file(filepath, "utf8\n", true);
	zn0w_utils::write_file(filepath, "default/data/test_schema_data\n", true);
}

// pseudo sql parser (for quick test)
bool analyse(std::string input)
{
	if (input == "create schema")
	{
		create_schema();
		return true;
	}
	else
		return false;
}

int main()
{
	/*std::cout << "" << std::endl;
	std::string input = "0";
	while (input != "")
	{
		std::cin >> input;
		bool d = analyse(input);
		if (d)
			std::cout << "The query has been executed" << std::endl;
		else
			std::cout << "Error: invalid query" << std::endl;
	}*/
	create_schema();
	system("pause");
}