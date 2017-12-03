#include "disasm.h"

#include <iostream>
#include <sstream>

namespace disasm
{
#define MASK(bits) (((uint64_t)1 << bits) - 1)
#define BITS_AT(value, position, nbits) ((value >> position) & MASK(nbits))

	typedef std::unique_ptr<instruction> inst_ptr;

	void decode_header(instruction* inst, uint64_t opcode)
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

	inst_ptr decode_alu_op(uint64_t opcode)
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

		return inst_ptr(op);
	}
	inst_ptr decode_alu_small_imm_op(uint64_t opcode)
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

		return inst_ptr(op);
	}
	inst_ptr decode_branch_op(uint64_t opcode)
	{
		branch* op = new branch;

		decode_header(op, opcode);

		op->immediate = BITS_AT(opcode, 0, 32);

		return inst_ptr(op);
	}
	inst_ptr decode_load_imm32(uint64_t opcode)
	{
		load_imm32* op = new load_imm32;

		decode_header(op, opcode);

		op->immediate = BITS_AT(opcode, 0, 32);

		return inst_ptr(op);
	}
	inst_ptr decode_load_imm_per_elmt_signed(uint64_t opcode)
	{
		load_imm_per_elmt_signed* op = new load_imm_per_elmt_signed;

		decode_header(op, opcode);

		op->per_elmt_ms_bit = BITS_AT(opcode, 16, 16);
		op->per_elmt_ls_bit = BITS_AT(opcode, 00, 16);

		return inst_ptr(op);
	}
	inst_ptr decode_load_imm_per_elmt_unsigned(uint64_t opcode)
	{
		load_imm_per_elmt_unsigned* op = new load_imm_per_elmt_unsigned;

		decode_header(op, opcode);

		op->per_elmt_ms_bit = BITS_AT(opcode, 16, 16);
		op->per_elmt_ls_bit = BITS_AT(opcode, 00, 16);

		return inst_ptr(op);
	}
	inst_ptr decode_semaphore(uint64_t opcode)
	{
		semaphore_inst* op = new semaphore_inst;

		decode_header(op, opcode);

		op->sa        = BITS_AT(opcode, 4, 1);
		op->semaphore = BITS_AT(opcode, 0, 4);

		return inst_ptr(op);
	}

	void disasm(
		const std::vector<uint64_t>& input_vec,
		std::vector<inst_ptr>& output)
	{
		for (auto input : input_vec)
		{
			uint64_t sig    = BITS_AT(input, 60, 4);
			uint64_t unpack = BITS_AT(input, 57, 3);
			
			switch (sig)
			{
			case 0b1110:
				switch (unpack)
				{
				case 0b000:
					output.emplace_back(decode_load_imm32(input));
					break;
				case 0b001:
					output.emplace_back(decode_load_imm_per_elmt_signed(input));
					break;
				case 0b011:
					output.emplace_back(decode_load_imm_per_elmt_unsigned(input));
					break;
				case 0b100:
					output.emplace_back(decode_semaphore(input));
					break;
				default:
					throw std::logic_error("Invalid Opcode Found");
				}
				break;
			case 0b1101:
				output.emplace_back(decode_alu_small_imm_op(input));
				break;
			case 0b1111:
				output.emplace_back(decode_branch_op(input));
				break;
			default:
				output.emplace_back(decode_alu_op(input));
				break;
			}
		}
	}
}