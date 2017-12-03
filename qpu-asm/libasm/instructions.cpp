
#include "instructions.h"

namespace qpuasm
{
	// Refer to VideoCodeIV Architecture Guide
	// p. 26 for relevant information

	
	uint64_t alu::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)sig       << 60;
		inst |= (uint64_t)unpack    << 57;
		inst |= (uint64_t)pm        << 56;
		inst |= (uint64_t)pack      << 52;
		inst |= (uint64_t)cond_add  << 49;
		inst |= (uint64_t)cond_mul  << 46;
		inst |= (uint64_t)sf        << 45;
		inst |= (uint64_t)ws        << 44;
		inst |= (uint64_t)waddr_add << 38;
		inst |= (uint64_t)waddr_mul << 32;
		inst |= (uint64_t)op_mul    << 29;
		inst |= (uint64_t)op_add    << 24;
		inst |= (uint64_t)raddr_a   << 18;
		inst |= (uint64_t)raddr_b   << 12;
		inst |= (uint64_t)add_a     << 9;
		inst |= (uint64_t)add_b     << 6;
		inst |= (uint64_t)mul_a     << 3;
		inst |= (uint64_t)mul_b     << 0;

		return inst;
	}
	uint64_t alu_small_imm::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)0b1101      << 60;
		inst |= (uint64_t)unpack      << 57;
		inst |= (uint64_t)pm          << 56;
		inst |= (uint64_t)pack        << 52;
		inst |= (uint64_t)cond_add    << 49;
		inst |= (uint64_t)cond_mul    << 46;
		inst |= (uint64_t)sf          << 45;
		inst |= (uint64_t)ws          << 44;
		inst |= (uint64_t)waddr_add   << 38;
		inst |= (uint64_t)waddr_mul   << 32;
		inst |= (uint64_t)op_mul      << 29;
		inst |= (uint64_t)op_add      << 24;
		inst |= (uint64_t)raddr_a     << 18;
		inst |= (uint64_t)small_immed << 12;
		inst |= (uint64_t)add_a       << 9;
		inst |= (uint64_t)add_b       << 6;
		inst |= (uint64_t)mul_a       << 3;
		inst |= (uint64_t)mul_b       << 0;

		return inst;
	}
	uint64_t branch::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)0b1111    << 60;
		/* unpack not present */
		/* pm not present */
		inst |= (uint64_t)pack      << 52;
		inst |= (uint64_t)cond_add  << 49;
		inst |= (uint64_t)cond_mul  << 46;
		inst |= (uint64_t)sf        << 45;
		inst |= (uint64_t)ws        << 44;
		inst |= (uint64_t)waddr_add << 38;
		inst |= (uint64_t)waddr_mul << 32;
		inst |= (uint64_t)immediate << 0;

		return inst;
	}
	uint64_t load_imm32::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)0b1110    << 60;
		inst |= (uint64_t)0b000     << 57;
		inst |= (uint64_t)pm        << 56;
		inst |= (uint64_t)pack      << 52;
		inst |= (uint64_t)cond_add  << 49;
		inst |= (uint64_t)cond_mul  << 46;
		inst |= (uint64_t)sf        << 45;
		inst |= (uint64_t)ws        << 44;
		inst |= (uint64_t)waddr_add << 38;
		inst |= (uint64_t)waddr_mul << 32;
		inst |= (uint64_t)immediate << 0;

		return inst;
	}
	uint64_t load_imm_per_elmt_signed::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)0b1110    << 60;
		inst |= (uint64_t)0b001     << 57;
		inst |= (uint64_t)pm        << 56;
		inst |= (uint64_t)pack      << 52;
		inst |= (uint64_t)cond_add  << 49;
		inst |= (uint64_t)cond_mul  << 46;
		inst |= (uint64_t)sf        << 45;
		inst |= (uint64_t)ws        << 44;
		inst |= (uint64_t)waddr_add << 38;
		inst |= (uint64_t)waddr_mul << 32;
		inst |= (uint64_t)per_element_ms_bit << 16;
		inst |= (uint64_t)per_element_ls_bit << 16;

		return inst;
	}
	uint64_t load_imm_per_elmt_unsigned::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)0b1110    << 60;
		inst |= (uint64_t)0b011     << 57;
		inst |= (uint64_t)pm        << 56;
		inst |= (uint64_t)pack      << 52;
		inst |= (uint64_t)cond_add  << 49;
		inst |= (uint64_t)cond_mul  << 46;
		inst |= (uint64_t)sf        << 45;
		inst |= (uint64_t)ws        << 44;
		inst |= (uint64_t)waddr_add << 38;
		inst |= (uint64_t)waddr_mul << 32;
		inst |= (uint64_t)per_element_ms_bit << 16;
		inst |= (uint64_t)per_element_ls_bit << 16;

		return inst;
	}
	uint64_t semaphore::encoded_instruction() const
	{
		uint64_t inst = 0;

		inst |= (uint64_t)0b1110     << 60;
		inst |= (uint64_t)0b100      << 57;
		inst |= (uint64_t)pm         << 56;
		inst |= (uint64_t)pack       << 52;
		inst |= (uint64_t)cond_add   << 49;
		inst |= (uint64_t)cond_mul   << 46;
		inst |= (uint64_t)sf         << 45;
		inst |= (uint64_t)ws         << 44;
		inst |= (uint64_t)waddr_add  << 38;
		inst |= (uint64_t)waddr_mul  << 32;
		inst |= (uint64_t)sa         << 4;
		inst |= (uint64_t)_semaphore << 0;

		return inst;
	}

	/* Constructors */
	instruction::instruction(const inst_base& base) :
		sig(base.sig),
		unpack(base.unpack),
		pm(base.pm),
		pack(base.pack),
		cond_add(base.cond_add),
		cond_mul(base.cond_mul),
		sf(base.sf),
		ws(base.ws),
		waddr_add(base.waddr_add),
		waddr_mul(base.waddr_mul)
	{

	}
	alu::alu(const inst_base& base, const alu_base& alu) :
		instruction(base),
		op_mul(alu.op_mul),
		op_add(alu.op_add),
		raddr_a(alu.raddr_a),
		raddr_b(alu.raddr_b),
		add_a(alu.add_a),
		add_b(alu.add_b),
		mul_a(alu.mul_a),
		mul_b(alu.mul_b)
	{

	}
	alu_small_imm::alu_small_imm(
		const inst_base& base,
		const alu_small_imm_base& alu) :
		instruction(base),
		op_mul(alu.op_mul),
		op_add(alu.op_add),
		raddr_a(alu.raddr_a),
		small_immed(alu.small_immed),
		add_a(alu.add_a),
		add_b(alu.add_b),
		mul_a(alu.mul_a),
		mul_b(alu.mul_b)
	{

	}
	branch::branch(const inst_base& base, uint<32> immed) :
		instruction(base),
		immediate(immed)
	{

	}
	load_imm32::load_imm32(const inst_base& base, uint<32> immed) :
		instruction(base),
		immediate(immed)
	{

	}
	load_imm_per_elmt_signed::load_imm_per_elmt_signed(
		const inst_base& base,
		uint<16> per_elmt_ms_bit,
		uint<16> per_elmt_ls_bit) :
		instruction(base),
		per_element_ms_bit(per_elmt_ms_bit),
		per_element_ls_bit(per_elmt_ls_bit)
	{

	}
	load_imm_per_elmt_unsigned::load_imm_per_elmt_unsigned(
		const inst_base& base,
		uint<16> per_elmt_ms_bit,
		uint<16> per_elmt_ls_bit) :
		instruction(base),
		per_element_ms_bit(per_elmt_ms_bit),
		per_element_ls_bit(per_elmt_ls_bit)
	{

	}
	semaphore::semaphore(
		const inst_base& base,
		uint<1> sa,
		uint<4> semaphore) :
		instruction(base),
		sa(sa),
		_semaphore(semaphore)
	{

	}
}

