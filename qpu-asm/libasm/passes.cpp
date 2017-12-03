#include "passes.h"
#include "instructions.h"

namespace qpuasm
{
	void print_binary(
		const std::vector<std::unique_ptr<instruction>>& instructions,
		std::vector<uint64_t>& output);

	void read_binary(
		const std::vector<uint64_t>& binary,
		std::vector<std::unique_ptr<instruction>>& output)
	{

	}

}
