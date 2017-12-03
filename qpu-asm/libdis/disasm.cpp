#include "disasm.h"

#include <iostream>
#include <sstream>

namespace disasm
{
#define MASK(bits) (((uint64_t)1 << bits) - 1)
#define BITS_AT(value, position, nbits) ((value >> position) & MASK(nbits))

	void decode_header(instruction* inst, std::uint64_t opcode)
	{
		inst->sig       = BITS_AT(opcode, 60, 4);
		inst->unpack    = BITS_AT(opcode, 57, 3);
		inst->pm        = BITS_AT(opcode, 56, 1);
		inst->pack      = BITS_AT(opcode, 52, 4);
		inst->cond_add  = BITS_AT(opcode, 49, 3);
		inst->cond_mul  = BITS_AT(opcode, 46, 3);
		inst->sf        = BITS_AT(opcode, 45, 1);
		inst->ws        = BITS_AT(opcode, 44, 1);
		inst->waddr_add = BITS_AT(opcode, 38, 6);
		inst->waddr_mul = BITS_AT(opcode, 32, 6);
	}

	std::unique_ptr<instruction> decode_alu_op(std::uint64_t opcode)
	{
		alu* op = new alu;

		decode_header(op, opcode);

		op->op_mul  = BITS_AT(opcode, 29, 3);
		op->op_add  = BITS_AT(opcode, 24, 5);
		op->raddr_a = BITS_AT(opcode, 18, 6);
		op->raddr_b = BITS_AT(opcode, 12, 6);
		op->add_a   = BITS_AT(opcode, 9, 3);
		op->add_b   = BITS_AT(opcode, 6, 3);
		op->mul_a   = BITS_AT(opcode, 3, 3);
		op->mul_b   = BITS_AT(opcode, 0, 3);

		return std::unique_ptr<instruction>(op);
	}

	std::unique_ptr<instruction> decode_alu_small_imm_op(std::uint64_t opcode)
	{
		alu_small_imm* op = new alu_small_imm;

		decode_header(op, opcode);

		op->op_mul      = BITS_AT(opcode, 29, 3);
		op->op_add      = BITS_AT(opcode, 24, 5);
		op->raddr_a     = BITS_AT(opcode, 18, 6);
		op->small_immed = BITS_AT(opcode, 12, 6);
		op->add_a       = BITS_AT(opcode, 9, 3);
		op->add_b       = BITS_AT(opcode, 6, 3);
		op->mul_a       = BITS_AT(opcode, 3, 3);
		op->mul_b       = BITS_AT(opcode, 0, 3);

		return std::unique_ptr<instruction>(op);
	}

	std::unique_ptr<instruction> decode_branch_op(std::uint64_t opcode)
	{
		branch* op = new branch;

		decode_header(op, opcode);

		op->immediate = BITS_AT(opcode, 0, 32);

		return std::unique_ptr<instruction>(op);
	}

	void disasm(
		const std::uint64_t* input, size_t n_input,
		std::vector<std::unique_ptr<instruction>>& output)
	{
		for (size_t i = 0; i < n_input; ++i)
		{
			uint64_t sig = BITS_AT(input[i], 60, 4);
			
			switch (sig)
			{
			case 0b1101:
				output.emplace_back(decode_alu_small_imm_op(input[i]));
				break;
			case 0b1111:
				output.emplace_back(decode_branch_op(input[i]));
				break;
			default:
				output.emplace_back(decode_alu_op(input[i]));
				break;
			}
		}
	}
}