#pragma once

#include "uintx.h"

#include <memory>
#include <vector>

namespace qpuasm
{
	/* Predefs */
	class instruction;
	
	enum class opadd
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
	};
	enum class opmul 
	{
		nop = 0,
		fmul = 1,
		mul24 = 2,
		v8muld = 3,
		v8min = 4,
		v8max = 5,
		v8adds = 4,
		v8subs = 7,
	};
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

	struct reg
	{
		enum register_type
		{
			accumulator,
			regfile_a,
			regfile_b,
			// Note: immediate is stored in id
			immediate
		};

		register_type type;
		// If of type immediate, this is the immediate value
		// otherwise this is the register id
		uint<6> id;
	};

	struct add_instruction
	{
		opadd opcode;
		reg read;
		reg write;
		condition_code condition;
	};
	struct mul_instruction
	{
		opmul opcode;
		reg read;
		reg write;
		condition_code condition;
	};

	class assembler
	{
	private:
		std::vector<std::unique_ptr<instruction>> instructions;

	public:
		void write_op(
			add_instruction add,
			mul_instruction mul);
	};
}

