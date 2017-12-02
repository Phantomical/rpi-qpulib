#pragma once

namespace qpuasm
{
	enum class condition_code
	{
		never = 0,
		always = 1,
		ZS = 2,
		ZC = 3,
		NS = 4,
		NC = 5,
		CS = 6,
		CC = 7
	};
}
