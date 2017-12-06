#pragma once

#include "device.h"
#include "registers.h"

#include <cstdint>
#include <unordered_map>

namespace qpu
{
	struct program
	{
		buffer* code;
		buffer* uniforms;
		uint32_t uniforms_size;
	};

	struct semaphore
	{
		bool value;
	};

	struct buffer
	{
		void* mapptr;
		uint32_t bufptr;
		uint32_t size;
	};

	struct invocation
	{

	};

	class driver
	{
	private:
		std::unordered_map<buffer*, uint32_t> buffer_refcount;
		std::unordered_map<program*, uint32_t> program_refcount;
		std::unordered_map<semaphore*, uint32_t> semaphore_refcount;

		std::unordered_map<semaphore*, program*> semaphore_refs;
	};
}
