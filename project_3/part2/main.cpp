#include <fstream> 
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <iomanip>


class inodes
{
public:
	char name[8];
	int size;
	int block_pointers[8];
	int used;
	
	friend std::ostream& operator <<(std::ostream& stream, inodes& node);
};

std::ostream& operator <<(std::ostream& stream, inodes& node)
{
	for (auto e : node.name)
	{
		//std::cout << e << std::endl;
		if (e == '\0')
		{
			e = ' ';
		}

		stream << e;
	}

	stream << std::setw(4) << std::hex << node.size;
	for (auto e : node.block_pointers)
		stream << std::setw(4) << std::hex << e;
	stream << std::setw(4) << std::hex << node.used;

	return stream;
}

class super_block
{
public:
	char in_use[128];
	inodes node[16];
};

class my_file_system: public super_block
{
private:
	std::string disk_name;


	void load(std::string& aux)
	{
		int pointer;

		for (pointer = 0; pointer < 128; pointer++)
			in_use[pointer] = aux[pointer];

		for (int i = 0; i < 16; i++)
			set_node(aux, pointer,i);

	}

	void set_node(std::string& aux, int& pointer,int i)
	{
		//set the name of the file
		for (int j = 0; j < 8; j++)
		{
			node[i].name[j] = aux[pointer];
			pointer++;
		}
		auto x = aux.substr(pointer,4);

		//set the size of the file	
		node[i].size = std::stoi(aux.substr(pointer, 4),0,16);
		pointer += 4;

		//set the pointers of the file	
		for (int k = 0; k < 8; k++)
		{
			node[i].block_pointers[k] = std::stoi(aux.substr(pointer,4),0,16);
			pointer += 4;
		}

		//set if the file is used
		node[i].used = std::stoi(aux.substr(pointer,4), 0, 16);
		pointer += 4;

	}

	void save()
	{
		std::ofstream file;
		file.open(disk_name, std::ios::out);

		if (file.is_open())
		{
			file.seekp(0);

			for (auto e : in_use)
				file << e;
			for (auto e : node)
				file << e;
		}
		else
			std::cout << "Failed to open the file"<<std::endl;

		file.close();
	}

public:



	my_file_system(std::string disk_name)
	{
		// Open the file with name diskName

		// Read the first 1KB and parse it to structs/objecs representing the super block
		// 	An easy way to work with the 1KB memory chunk is to move a pointer to a
		//	position where a struct/object begins. You can use the sizeof operator to help
		//	cleanly determine the position. Next, cast the pointer to a pointer of the
		//	struct/object type.

		// Be sure to close the file in a destructor or otherwise before
		// the process exits.

		this->disk_name = disk_name;

		std::ifstream file;
		file.open(disk_name, std::ios::in);

		if (file.is_open())
		{
			char  aux[1024];
			
			file.read(aux, 1024);

			std::string s(std::move(aux));
			
			load(s);
		}
		else
			std::cout << "Failed to load the file"<<std::endl;

		file.close();
	}


	int create(char name[8], int size)
	{ //create a file with this name and this size

	  // high level pseudo code for creating a new file

	  // Step 1: Look for a free inode by searching the collection of objects
	  // representing inodes within the super block object.
	  // If none exist, then return an error.
	  // Also make sure that no other file in use with the same name exists.

	  // Step 2: Look for a number of free blocks equal to the size variable
	  // passed to this method. If not enough free blocks exist, then return an error.

	  // Step 3: Now we know we have an inode and free blocks necessary to
	  // create the file. So mark the inode and blocks as used and update the rest of
	  // the information in the inode.

	  // Step 4: Write the entire super block back to disk.
	  //	An easy way to do this is to seek to the beginning of the disk
	  //	and write the 1KB memory chunk.

		int first_free = -1;
		for (int i = 0; i < 16; i++)
		{
			if (first_free == -1 && !node[i].used)
				first_free = i;

			if (strcmp(name,node[i].name) == 0)
			{
				std::cout << "File with the same name already exists" << std::endl;
				return -1;
			}
		}

		if (first_free >= 0)
		{
			int count = 0;
			std::vector<int> free_blocks;
			for (int i = 0; i < 128; i++)
			{
				if (in_use[i] =='0')
				{
					free_blocks.push_back(i);
					if (free_blocks.size() == size)
						break;
				}
			}

			if (free_blocks.size() > 0)
			{
				strcpy(node[first_free].name, name);
				node[first_free].size = size;
				node[first_free].used = 1;
				
				for (int j = 0; j < free_blocks.size(); j++)
				{
					node[first_free].block_pointers[j] = free_blocks[j];
					in_use[free_blocks.at(j)] = '1';
				}

				save();
			}
			else
			{
				std::cout << "Failed to find a free block" << std::endl;
				return -1;
			}
		}
		else
		{
			std::cout << "Failed to find a free inode" << std::endl;
			return -1;
		}
		///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
		///	does not specify if I should remove the blocks too
		return 0;
	}



	int del(char name[8])
	{
		// Delete the file with this name

		// Step 1: Look for an inode that is in use with given name
		// by searching the collection of objects
		// representing inodes within the super block object.
		// If it does not exist, then return an error.

		// Step 2: Free blocks of the file being deleted by updating
		// the object representing the free block list in the super block object.

		// Step 3: Mark inode as free.

		// Step 4: Write the entire super block back to disk.

		for (auto &n : node)
		{
			if (strcmp(n.name, name) == 0)
			{
				n.used = 0;
				n.size = 0;
				
				for (auto& e : n.block_pointers)
					in_use[e] = '0';
				for (auto& e : n.name)
					e = 0;
				for (auto& e : n.block_pointers)
					e = 0;

				save();
			}
			else
			{
				std::cout << "Inode does not exist" << std::endl;
			}
		}
		
		return 0;
	} 


	int ls(void)
	{
		// List names of all files on disk

		// Step 1: Print the name and size fields of all used inodes.

		std::cout << "List of files:" << std::endl;
		for (auto n : node)
		{
			std::string aux;
			for (auto e : n.name)
			{
				
				if (e == '\0')
				{
					e = ' ';
				}

				aux += e;
			}

			std::cout << "    " << aux << " " << n.size << std::endl;
		}


		

		return 0;
	}

	int read(char name[8], int blockNum, char buf[1024])
	{

		// read this block from this file
		// Return an error if and when appropriate. For instance, make sure
		// blockNum does not exceed size-1.

		// Step 1: Locate the inode for this file as in Step 1 of delete.

		// Step 2: Seek to blockPointers[blockNum] and read the block
		// from disk to buf.

		for (auto& n : node)
		{
			if (strcmp(n.name, name) == 0)
			{
				if (n.size < blockNum)
				{
					std::cout << "The does not contain " << blockNum << " blocks" << std::endl;
					return -1;
				}

				std::ifstream file;
				file.open(disk_name, std::ios::in);

				if (file.is_open())
				{
					char aux[1024];

					file.seekg(((int)n.block_pointers[blockNum]) * 1024);
					file.read(aux, 1024);
				}
				else
					std::cout << "Failed to load the file" << std::endl;

				file.close();

				break;
			}
			else
				std::cout << "File does not exist" << std::endl;
		}
		
		return 0;
	}


	int write(char name[8], int blockNum, char buf[1024])
	{

		// write this block to this file
		// Return an error if and when appropriate.

		// Step 1: Locate the inode for this file as in Step 1 of delete.

		// Step 2: Seek to blockPointers[blockNum] and write buf to disk.

		for (auto& n : node)
		{
			if (strcmp(n.name, name) == 0)
			{
				if (n.size < blockNum)
				{
					std::cout << "The does not contain " << blockNum << " blocks" << std::endl;
					return -1;
				}

				std::ofstream file;
				file.open(disk_name, std::ios::out);

				if (file.is_open())
				{
					file.seekp((int)n.block_pointers[blockNum] * 1024);
					file<<buf;
				}
				else
					std::cout << "Failed to load the file" << std::endl;

				file.close();

				break;
			}
			else
				std::cout << "File does not exist" << std::endl;
		}

		return 0;
	}
};


void run(std::ifstream& file)
{
	
	int n;
	char file_name[8], buffer[1024];

	std::string disk_name;
	file >> disk_name;

	my_file_system s(disk_name);

	int counter = 0;

	char command;
	while (file >> command)
	{
		counter++;
		if (command == 'C')
		{
			file >> file_name >> n;

			s.create(file_name, n);
		}
		else if (command == 'D')
		{
			file >> file_name;

			s.del(file_name);
		}
		else if (command == 'L')
		{
			s.ls();
		}
		else if (command == 'R')
		{
			file >> file_name >> n;

			s.read(file_name, n, buffer);
		}
		else if (command == 'W')
		{
			file >> file_name >> n;

			s.write(file_name, n, buffer);
		}
		else
		{
			std::cout << "Invalid Command" << std::endl;
		}
	}

}

int main()
{

	std::ifstream file;
	file.open("input.txt", std::ios::in);

	if (file.is_open())
	{
		run(file);
	}
	else
		std::cout << "Failed to load the file"<<std::endl;

	file.close();

}