#include <fstream> 
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	std::ofstream file ("disk0", std::ios::out | std::ios::trunc);

	
	file << 1;
	for(int i=0;i<131071;i++)
		file<<0;

	file.close();

	return 0;
}