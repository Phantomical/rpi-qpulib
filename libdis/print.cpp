#include "disasm.h"

#include <bitset>
#include <sstream>
#include <cassert>
#include <iostream>
#include <iterator>

namespace disasm
{
	template<typename T, size_t N>
	constexpr size_t size(const T(&array)[N])
	{
		return N;
	}

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
			case 32: return "r0";
			case 33: return "r1";
			case 34: return "r2";
			case 35: return "r3";
			case 36: return "TMU_NOSWAP";
			case 37: return "r5";
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

		assert(mux < size(muxtable));

		return muxtable[mux];
	}
	std::string hex(uint64_t val)
	{
		std::stringstream ss;
		ss << std::hex << val << 'h';
		return ss.str();
	}
	const char* cond(uint64_t cond)
	{
		static const char* cond_codes[] = {
			"never",
			"always",
			"ZS",
			"ZC",
			"NS",
			"NC",
			"CS",
			"CC"
		};

		assert(cond < size(cond_codes));

		return cond_codes[cond];
	}
	const char* signal(uint64_t signal)
	{
		const char* signal_meanings[] = {
			"[0] Software Breakpoint",
			"[1] No Signal",
			"[2] Thread Switch (not last)",
			"[3] Program End",
			"[4] Wait for Scoreboard",
			"[5] Scoreboard Unlock",
			"[6] Last Thread Switch",
			"[7] Coverage load from Tile Buffer to r4",
			"[8] Color Load from Tile Buffer to r4",
			"[9] Color Load and Program End",
			"[10] Load data from TMU0 to r4",
			"[11] Load data from TMU1 to r4",
			"[12] Alpha-Mask Load for Tile Buffer to r4",
			"[13] Small Immediate ALU Instruction",
			"[14] Load Immediate Instruction",
			"[15] Branch Instruction"
		};

		assert(signal < size(signal_meanings));

		return signal_meanings[signal];
	}

	const char* ra_unpack(uint64_t unpack)
	{
		static const char* unpack_vals[] = {
			"nop",
			"16a -> 32",
			"16b -> 32",
			"8d rep -> 32",
			"8a -> 32",
			"8b -> 32",
			"8c -> 32",
			"8d -> 32"
		};

		assert(unpack < size(unpack_vals));

		return unpack_vals[unpack];
	}
	const char* ra_pack(uint64_t pack)
	{
		static const char* pack_vals[] = {
			"nop",
			"32 -> 16a",
			"32 -> 16b",
			"32 -> 8888",
			"32 -> 8a",
			"32 -> 8b",
			"32 -> 8c",
			"32 -> 8d",
			"32 -> 32 sat",
			"32 -> 16a sat",
			"32 -> 16b sat",
			"32 -> 8888 sat",
			"32 -> 8a sat",
			"32 -> 8b sat",
			"32 -> 8c sat",
			"32 -> 8d sat"
		};

		assert(pack < size(pack_vals));

		return pack_vals[pack];
	}
	const char* r4_unpack(uint64_t pack)
	{
		static const char* pack_vals[] = {
			"nop",
			"16a -> 32",
			"16b -> 32",
			"8d rep -> 32",
			"8a -> 32",
			"8b -> 32",
			"8c -> 32",
			"8d -> 32"
		};

		assert(pack < size(pack_vals));

		return pack_vals[pack];
	}
	const char* mul_pack(uint64_t pack)
	{
		switch (pack)
		{
		case 0: return "nop";
		case 3: return "32 -> 8888";
		case 4: return "32 -> 8a";
		case 5: return "32 -> 8b";
		case 6: return "32 -> 8c";
		case 7: return "32 -> 8d";
		default:return "#UNKNOWN#";
		}
	}

	const char* unpack_m(uint64_t pm, uint64_t unpack)
	{
		if (!pm)
			return ra_unpack(unpack);
		return r4_unpack(unpack);
	}
	const char* pack_m(uint64_t pm, uint64_t pack)
	{
		if (!pm)
			return ra_pack(pack);
		return mul_pack(pack);
	}

	std::ostream& instruction::print(std::ostream& os) const
	{
		return os
			<< "\tsig: " << signal(sig) << '\n'
			<< "\tunpack: " << unpack_m(pm, unpack) << '\n'
			<< "\tpm: " << pm << '\n'
			<< "\tpack: " << pack_m(pm, pack) << '\n'
			<< "\tcond_add: " << cond(cond_add) << '\n'
			<< "\tcond_mul: " << cond(cond_mul) << '\n'
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
			<< "\timmediate: " << hex(immediate) << '\n';
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
