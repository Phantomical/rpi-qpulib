#pragma once

#include <cstdint>

namespace disasm
{

	struct reg
	{
		enum
		{
			accumulator,
			regfile_a,
			regfile_b,
			small_immed
		};

		uint8_t id : 6;
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

	struct add_op
	{
		enum opcode_val
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
			v8adds = 30,
			v8subs = 31
		};

		opcode_val opcode;
		reg write;
		reg read1;
		reg read2;
		condition_code cond;
		uint8_t pack : 4;
		uint8_t unpack : 3;
	};
	struct mul_op
	{
		enum opcode_val
		{
			nop = 0,
			fmul = 1,
			mul24 = 2,
			v8muld = 3,
			v8min = 4,
			v8max = 5,
			v8ads = 6,
			v8subs = 7
		};

		opcode_val opcode;
		reg write;
		reg read1;
		reg read2;
		condition_code cond;
		uint8_t pack : 4;
		uint8_t unpack : 3;
	};
	struct ldtmu
	{
		uint8_t tmu_id : 1;
	};
	struct branch
	{
		enum branch_cond
		{
			allZset = 0,
			allZclear = 1,
			anyZset = 2,
			anyZclear = 3,
			allNset = 4,
			allNclear = 5,
			anyNset = 6,
			anyNclear = 7,
			allCset = 8,
			allCclear = 9,
			anyCset = 10,
			anyCclear = 11,
			/* 12-14 reserved */
			always = 15
		};

		branch_cond cond;
		uint8_t relative : 1;
		uint8_t use_reg : 1;
		reg read;
		reg write1;
		reg write2;
		int32_t offset;
	};
	struct semaphore
	{
		uint8_t pm : 1;
		uint8_t pack : 4;

		reg write_add;
		reg write_mul;

		uint8_t sa : 1;
		uint8_t semaphore : 4;
	};
	struct ldi
	{

	};
}
