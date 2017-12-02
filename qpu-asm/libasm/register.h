#pragma once

#include "uintx.h"

namespace qpuasm
{
	struct reg
	{
		enum reg_type
		{
			accumulator,
			regfile_a,
			regfile_b,
			small_immed
		} type;

		uint<6> value;
	};
}
