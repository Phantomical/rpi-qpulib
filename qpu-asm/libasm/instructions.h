#ifndef LIBQPUASM_INSTRUCTIONS_H
#define LIBQPUASM_INSTRUCTIONS_H

#include "uintx.h"

#include <cstdint>
#include <memory>

namespace qpuasm
{
	enum class add_op
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
	enum class mul_op
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
	
	struct inst_base
	{
		uint<4> sig;
		uint<3> unpack;
		uint<1> pm;
		uint<4> pack;
		uint<3> cond_add;
		uint<3> cond_mul;
		uint<1> sf;
		uint<1> ws;
		uint<6> waddr_add;
		uint<6> waddr_mul;
	};
	struct alu_base
	{
		uint<3> op_mul;
		uint<5> op_add;
		uint<6> raddr_a;
		uint<6> raddr_b;
		uint<3> add_a;
		uint<3> add_b;
		uint<3> mul_a;
		uint<3> mul_b;
	};
	struct alu_small_imm_base
	{
		uint<3> op_mul;
		uint<5> op_add;
		uint<6> raddr_a;
		uint<6> small_immed;
		uint<3> add_a;
		uint<3> add_b;
		uint<3> mul_a;
		uint<3> mul_b;
	};

	class instruction
	{
	protected:
		uint<4> sig;
		uint<3> unpack;
		uint<1> pm;
		uint<4> pack;
		uint<3> cond_add;
		uint<3> cond_mul;
		uint<1> sf;
		uint<1> ws;
		uint<6> waddr_add;
		uint<6> waddr_mul;

		instruction(const inst_base& base);

	public:
		virtual uint64_t encoded_instruction() const = 0;

		virtual ~instruction() = 0;
	};

	class alu : public instruction
	{
	private:
		uint<3> op_mul;
		uint<5> op_add;
		uint<6> raddr_a;
		uint<6> raddr_b;
		uint<3> add_a;
		uint<3> add_b;
		uint<3> mul_a;
		uint<3> mul_b;

	public:
		virtual uint64_t encoded_instruction() const override;

		alu(const inst_base& base, const alu_base& alu);
	};

	class alu_small_imm : public instruction
	{
	private:
		uint<3> op_mul;
		uint<5> op_add;
		uint<6> raddr_a;
		uint<6> small_immed;
		uint<3> add_a;
		uint<3> add_b;
		uint<3> mul_a;
		uint<3> mul_b;

	public:
		virtual uint64_t encoded_instruction() const override;

		alu_small_imm(
			const inst_base& base,
			const alu_small_imm_base& alu);
	};

	class branch : public instruction
	{
	private:
		uint<32> immediate;

	public:
		virtual uint64_t encoded_instruction() const override;

		branch(
			const inst_base& base,
			uint<32> immed);
	};

	class load_imm32 : public instruction
	{
	private:
		uint<32> immediate;

	public:
		virtual uint64_t encoded_instruction() const override;

		load_imm32(
			const inst_base& base,
			uint<32> immed);
	};

	class load_imm_per_elmt_signed : public instruction
	{
	private:
		uint<16> per_element_ms_bit;
		uint<16> per_element_ls_bit;

	public:
		virtual uint64_t encoded_instruction() const override;

		load_imm_per_elmt_signed(
			const inst_base& base,
			uint<16> per_elmt_ms_bit,
			uint<16> per_elmt_ls_bit);
	};

	class load_imm_per_elmt_unsigned : public instruction
	{
	private:
		uint<16> per_element_ms_bit;
		uint<16> per_element_ls_bit;

	public:
		virtual uint64_t encoded_instruction() const override;

		load_imm_per_elmt_unsigned(
			const inst_base& base,
			uint<16> per_elmt_ms_bit,
			uint<16> per_elmt_ls_bit);
	};

	class semaphore : public instruction
	{
	private:
		uint<1> sa;
		uint<4> _semaphore;

	public:
		virtual uint64_t encoded_instruction() const override;

		semaphore(
			const inst_base& base,
			uint<1> sa,
			uint<4> semaphore);
	};
}

#endif
