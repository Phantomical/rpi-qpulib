
#include "assembler.h"
#include "instructions.h"

namespace qpuasm
{
	/* REGISTER CONFLICTS :
	 * A register conflict occurrs when the mul and add programs
	 * are writing to incompatible registers. This means that either:
	 *  - Both instructions write to the same register file
	 */

	void assembler::write_op(
		add_instruction add,
		mul_instruction mul)
	{
		inst_base base;
		alu_base alu;

		// Note: Check conditions (They can't both be present)
		base.cond_add = add.condition;
		base.cond_mul = mul.condition;

		// No signal
		base.sig = 1;

		
	}
}
