#pragma once

#include "register.h"
#include "condition_code.h"

namespace qpuasm
{
	struct add_op
	{
		enum add_op_opcode
		{
			nop = 0,
			fadd = 1,
			fsub = 2,
			fmin = 3,
			fmax = 4,
			fminabs = 5,
			fmaxabs = 6,
			ftoi = 7,
			itof = 8,
			/* 9-11 are reserved */
			add = 12,
			sub = 13,
			shr = 14,
			asr = 15,
			ror = 16,
			shl = 17,
			min = 18,
			max = 19,
			and = 20,
			or = 21,
			xor = 22,
			not = 23,
			clz = 24,
			/* 25-29 are reserved */
			v8adds = 30,
			v8subs = 31,
		} opcode;

		reg write;
		reg read1;
		reg read2;
	};
}
