#pragma once

#include "uintx.h"

#include <memory>
#include <vector>

namespace qpuasm
{
	class instruction;

	void print_binary(
		const std::vector<std::unique_ptr<instruction>>& instructions,
		std::vector<std::uint64_t>& output);

	void read_binary(
		const std::vector<std::uint64_t>& binary,
		std::vector<std::unique_ptr<instruction>>& output);

	class Assembler
	{

	};

	class Validator
	{

	};


}
