#include "disasm.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <bitset>

namespace disasm
{
	/* Print Implementations */
	const char* mul_op(uint64_t op)
	{
		switch (op)
		{
		case 0: return "nop";
		case 1: return "fmul";
		case 2: return "mul24";
		case 3: return "v8muld";
		case 4: return "v8min";
		case 5: return "v8max";
		case 6: return "v8adds";
		case 7: return "v8subs";
		default: return "#UNKNOWN#";
		}
	}
	const char* add_op(uint64_t op)
	{
		switch (op)
		{
		case 0: return "nop";
		case 1: return "fadd";
		case 2: return "fsub";
		case 3: return "fmin";
		case 4: return "fmax";
		case 5: return "fminabs";
		case 6: return "fmaxabs";
		case 7: return "ftoi";
		case 8: return "itof";
		case 12: return "add";
		case 13: return "sub";
		case 14: return "shr";
		case 15: return "asr";
		case 16: return "ror";
		case 17: return "shl";
		case 18: return "min";
		case 19: return "max";
		case 20: return "and";
		case 21: return "or";
		case 22: return "xor";
		case 23: return "not";
		case 24: return "clz";
		case 30: return "v8adds";
		case 31: return "v8subs";
		default: return "#UNKNOWN#";
		}
	}
	std::string reg(
		uint64_t regid,
		bool regfile_a,
		bool is_write)
	{

		if (regid < 32)
		{
			std::stringstream ss;
			ss << "r"
				<< (regfile_a ? 'a' : 'b')
				<< regid;
			return ss.str();
		}

		if (!is_write)
		{
			switch (regid)
			{
			case 32: return "UNIFORM_READ";
			case 35: return "VARYING_READ";
			case 38:
				if (regfile_a)
					return "ELEMENT_NUMBER";
				else
					return "QPU_NUMBER";
			case 39: return "NOP";
			case 41:
				if (regfile_a)
					return "X_PIXEL_COORD";
				else
					return "Y_PIXEL_COORD";
			case 42:
				if (regfile_a)
					return "MS_FLAGS";
				else
					return "REV_FLAG";
			case 48:
				return "VPM_READ";
			case 49:
				if (regfile_a)
					return "VPM_LD_BUSY";
				else
					return "VPM_ST_BUSY";
			case 50:
				if (regfile_a)
					return "VPM_LD_WAIT";
				else
					return "VPM_ST_WAIT";
			case 51: return "MUTEX_ACQUIRE";
			default: return "#UNKNOWN#";
			}
		}
		else
		{
			switch (regid)
			{
			case 32: return "ACC0";
			case 33: return "ACC1";
			case 34: return "ACC2";
			case 35: return "ACC3";
			case 36: return "TMU_NOSWAP";
			case 37: return "ACC5";
			case 38: return "HOST_INT";
			case 39: return "NOP";
			case 40: return "UNIFORMS_ADDRESS";
			case 41: 
				if (regfile_a)
					return "QUAD_X";
				else
					return "QUAD_Y";
			case 42: 
				if (regfile_a)
					return "MS_FLAGS";
				else
					return "REV_FLAG";
			case 43: return "TLB_STENCIL_SETUP";
			case 44: return "TLB_Z";
			case 45: return "TLB_COLOUR_MS";
			case 46: return "TLB_COLOUR_ALL";
			case 47: return "TLB_ALPHA_MASK";
			case 48: return "VPM_WRITE";
			case 49: 
				if (regfile_a)
					return "VPMVCD_RD_SETUP";
				else
					return "VPMVCD_WR_SETUP";
			case 50:
				if (regfile_a)
					return "VPM_LD_ADDR";
				else
					return "VPM_ST_ADDR";
			case 51: return "MUTEX_RELEASE";
			case 52: return "SFU_RECIP";
			case 53: return "SFU_RECIPSQRT";
			case 54: return "SFU_EXP";
			case 55: return "SFU_LOG";
			case 56: return "TMU0_S";
			case 57: return "TMU0_T";
			case 58: return "TMU0_R";
			case 59: return "TMU0_B";
			case 60: return "TMU1_S";
			case 61: return "TMU1_T";
			case 62: return "TMU1_R";
			case 63: return "TMU1_B";
			default: return "#UNKNOWN#";
			}
		}
	}
	const char* mux(uint64_t mux)
	{
		static const char* muxtable[] = {
			"r0",
			"r1",
			"r2",
			"r3",
			"r4",
			"r5",
			"Regfile A",
			"Regfile B"
		};

		assert(mux < std::size(muxtable));

		return muxtable[mux];
	}

	std::ostream& instruction::print(std::ostream& os) const
	{
		return os
			<< "\tsig: " << sig << '\n'
			<< "\tunpack: " << unpack << '\n'
			<< "\tpm: " << pm << '\n'
			<< "\tpack: " << pack << '\n'
			<< "\tcond_add: " << cond_add << '\n'
			<< "\tcond_mul: " << cond_mul << '\n'
			<< "\tsf: " << sf << '\n'
			<< "\tws: " << ws << '\n'
			<< "\twaddr_add: " << reg(waddr_add, !ws, 1) << '\n'
			<< "\twaddr_mul: " << reg(waddr_mul, ws, 1) << '\n';
	}
	std::ostream& alu::print(std::ostream& os) const
	{
		return instruction::print(os << "ALU Instruction:\n")
			<< "\top_mul: " << mul_op(op_mul) << '\n'
			<< "\top_add: " << add_op(op_add) << '\n'
			<< "\traddr_a: " << reg(raddr_a, 1, 0) << '\n'
			<< "\traddr_b: " << reg(raddr_b, 0, 0) << '\n'
			<< "\tadd_a: " << mux(add_a) << '\n'
			<< "\tadd_b: " << mux(add_b) << '\n'
			<< "\tmul_a: " << mux(mul_a) << '\n'
			<< "\tmul_b: " << mux(mul_b) << '\n';
	}
	std::ostream& alu_small_imm::print(std::ostream& os) const
	{
		return instruction::print(os << "ALU Instruction with Small Immediate:\n")
			<< "\top_mul: " << mul_op(op_mul) << '\n'
			<< "\top_add: " << add_op(op_add) << '\n'
			<< "\traddr_a: " << reg(raddr_a, 1, 0) << '\n'
			<< "\trsmall_immed: " << small_immed << '\n'
			<< "\tadd_a: " << mux(add_a) << '\n'
			<< "\tadd_b: " << mux(add_b) << '\n'
			<< "\tmul_a: " << mux(mul_a) << '\n'
			<< "\tmul_b: " << mux(mul_b) << '\n';
	}
	std::ostream& branch::print(std::ostream& os) const
	{
		return instruction::print(os << "Branch Instruction:\n")
			<< "\toffset: " << (int32_t)immediate << '\n';
	}
	std::ostream& load_imm32::print(std::ostream& os) const
	{
		return instruction::print(os << "Load Immediate Instruction:\n")
			<< "\timmediate: " << immediate << '\n';
	}
	std::ostream& load_imm_per_elmt_unsigned::print(std::ostream& os) const
	{
		return instruction::print(os << "Load Unsigned Per-Element Immediate:\n")
			<< "\tper-element MS bit: " << std::bitset<16>(per_elmt_ms_bit) << '\n'
			<< "\tper-element LS bit: " << std::bitset<16>(per_elmt_ls_bit) << '\n';
	}
	std::ostream& load_imm_per_elmt_signed::print(std::ostream& os) const
	{
		return instruction::print(os << "Load Signed Per-Element Immediate:\n")
			<< "\tper-element MS bit: " << std::bitset<16>(per_elmt_ms_bit) << '\n'
			<< "\tper-element LS bit: " << std::bitset<16>(per_elmt_ls_bit) << '\n';
	}
	std::ostream& semaphore_inst::print(std::ostream& os) const
	{
		return instruction::print(os << "Semaphore Instruction:\n")
			<< "\tsa: " << sa << '\n'
			<< "\tsemaphore: " << semaphore << '\n';
	}
}
