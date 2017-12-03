
#include "disasm.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <intrin.h>

std::vector<std::uint64_t> readfile(const char* filename)
{
	std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);

	if (!ifs)
		throw std::runtime_error(filename);

	decltype(ifs)::pos_type size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<char> vals(size);
	ifs.read(vals.data(), size);

	std::vector<uint64_t> words(size / sizeof(uint64_t));
	std::memcpy(words.data(), vals.data(), words.size() * sizeof(uint64_t));

	return words;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: qpu-dis <file>" << std::endl;
		return -1;
	}

	try
	{
		std::vector<uint64_t> binary = readfile(argv[1]);
		
		std::vector<std::unique_ptr<disasm::instruction>> instructions;
		disasm::disasm(binary.data(), binary.size(), instructions);

		//std::cout << std::hex;

		for (auto& inst : instructions)
		{
			inst->print(std::cout) << '\n';
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error: Unable to find file '"
			<< e.what()
			<< "'."
			<< std::endl;
		return 1;
	}

	return 0;
}
