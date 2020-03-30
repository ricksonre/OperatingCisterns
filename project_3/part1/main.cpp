#include <vector>
#include <fstream> 
#include <string>
#include <iostream>
#include <sstream>

typedef unsigned int byte;
using virtual_addresses = std::vector<byte>;

bool load_file(virtual_addresses& v, byte& n, byte& m)
{
	std::ifstream file;
	file.open("input.txt", std::ios::in);

	if (file.is_open())
	{
		std::string line;
		
		std::getline(file, line);
		n = std::stoi(line);
		
		std::getline(file, line);
		m = std::stoi(line);
		
		while(std::getline(file,line))
			v.push_back(std::stoi(line));

		
		file.close();

		return 1;
	}
	
	std::cout << "Failed to load the file";
	return 0;
}

void calculate(virtual_addresses& v, byte n, byte m)
{
	for (auto e : v)
	{
		int page_number, offset;

		page_number = (e>>n);
		offset = (e ^ (page_number << n));

		std::cout << "virtual address v1 is in page number " << page_number << " and offset " << offset << std::endl;;
	}
}

int main(int argc, char* argv[])
{
	byte n, m;
	virtual_addresses v;

	if (load_file(v, n, m))
	{
		calculate(v, n, m);
	}

	return 0;
}