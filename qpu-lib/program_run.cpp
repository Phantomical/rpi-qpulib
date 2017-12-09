
#include "device.h"
#include "mailbox.h"
#include "registers.h"

#include <new>
#include <cassert>
#include <cstdint>

namespace qpu
{
	using namespace reg;

	static constexpr uint32_t QPURQL_MASK   = 0b11111;
	static constexpr uint32_t QPURQERR_MASK = 1 << 7;
	static constexpr uint32_t QPURQCM_MASK  = 0xFF << 8;
	static constexpr uint32_t QPURQCC_MASK  = 0xFF << 16;

	static constexpr uint32_t QPURQL_RESET   = 1;
	static constexpr uint32_t QPURQERR_RESET = QPURQERR_RESET;
	static constexpr uint32_t QPURQCM_RESET  = 1 << 8;
	static constexpr uint32_t QPURQCC_RESET  = 1 << 16;

	uint32_t complete_programs()
	{
		// Read number of programs completed
		uint32_t completed = *V3D_SRQCS & QPURQCC_MASK;
		// Reset completed counter
		*V3D_SRQCS |= QPURQCC_RESET;

		return completed;
	}

	void start_program(
		uint32_t code_addr,
		uint32_t uniforms,
		uint32_t uniforms_length)
	{
		if (uniforms_length > 1024)
			uniforms_length = 1024;

		assert(code_addr != 0);

		do
		{
			// Clear the error bit
			*V3D_SRQCS |= QPURQERR_RESET;

			// Setup uniforms buffer
			*V3D_SRQUA = uniforms;
			*V3D_SRQUL = uniforms_length;

			// Put program into request FIFO
			*V3D_SRQPC = code_addr;

		} while (*V3D_SRQCS & QPURQERR_RESET);
	}

	semaphore* device::run_program(
		program* prog,
		buffer* uniforms)
	{
		semaphore* sema = new (std::nothrow) semaphore;

		if (!sema)
			return nullptr;

		sema->is_finished = false;
		sema->cleanup_func = [=]() {
			delete_program(prog);
			delete_buffer(uniforms);
		};

		{ // Increment reference counts
			auto it1 = program_refcounts.find(prog);
			auto it2 = buffer_refcounts.find(uniforms);

			assert(it1 != program_refcounts.end());
			assert(it2 != buffer_refcounts.end());

			it1->second++;
			it2->second++;
		}

		uint32_t code_buf = prog->code_buf->bus_addr;
		uint32_t buf_uniforms = 0;
		uint32_t buf_uniforms_length = 0;

		if (uniforms)
		{
			buf_uniforms = uniforms->bus_addr;
			buf_uniforms_length = uniforms->size;
		}

		start_program(
			code_buf, 
			buf_uniforms, 
			buf_uniforms_length);

		program_queue.push(sema);

		pump_queue();

		return sema;
	}

	void device::pump_queue()
	{
		uint32_t complete = complete_programs();

		for (uint32_t i = 0; i < complete; ++i)
		{
			assert(!program_queue.empty());

			semaphore* sema = program_queue.front();
			program_queue.pop();

			sema->is_finished = true;
			sema->cleanup_func();
		}
	}
}
