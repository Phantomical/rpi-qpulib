#ifndef DISASM_H
#define DISASM_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iosfwd>

namespace disasm
{
	struct instruction
	{
		std::uint32_t sig : 4;
		std::uint32_t unpack : 3;
		std::uint32_t pm : 1;
		std::uint32_t pack : 4;
		std::uint32_t cond_add : 3;
		std::uint32_t cond_mul : 3; 
		std::uint32_t sf : 1;
		std::uint32_t ws : 1;
		std::uint32_t waddr_add : 6;
		std::uint32_t waddr_mul : 6;

		virtual std::ostream& print(std::ostream& o) const;
	};

	struct alu : instruction
	{
		std::uint32_t op_mul : 3;
		std::uint32_t op_add : 5;
		std::uint32_t raddr_a : 6;
		std::uint32_t raddr_b : 6;
		std::uint32_t add_a : 3;
		std::uint32_t add_b : 3;
		std::uint32_t mul_a : 3;
		std::uint32_t mul_b : 3;

		virtual std::ostream& print(std::ostream& o) const override;
	};
	struct alu_small_imm : instruction
	{
		std::uint32_t op_mul : 3;
		std::uint32_t op_add : 5;
		std::uint32_t raddr_a : 6;
		std::uint32_t small_immed : 6;
		std::uint32_t add_a : 3;
		std::uint32_t add_b : 3;
		std::uint32_t mul_a : 3;
		std::uint32_t mul_b : 3;

		virtual std::ostream& print(std::ostream& o) const override;
	};
	struct branch : instruction
	{
		uint32_t immediate;

		virtual std::ostream& print(std::ostream& o) const override;
	};
	struct load_imm32 : instruction
	{
		uint32_t immediate;

		virtual std::ostream& print(std::ostream& o) const override;
	};
	struct load_imm_per_elmt_unsigned : instruction
	{
		uint16_t per_elmt_ms_bit;
		uint16_t per_elmt_ls_bit;

		virtual std::ostream& print(std::ostream& o) const override;
	};
	struct load_imm_per_elmt_signed : instruction
	{
		uint16_t per_elmt_ms_bit;
		uint16_t per_elmt_ls_bit;

		virtual std::ostream& print(std::ostream& o) const override;
	};
	struct semaphore_inst : instruction
	{
		uint8_t sa : 1;
		uint8_t semaphore : 4;

		virtual std::ostream& print(std::ostream& o) const override;
	};

	void disasm(
		const std::vector<uint64_t>& input,
		std::vector<std::unique_ptr<instruction>>& output);

	void decompile(

	);

}


#endif
