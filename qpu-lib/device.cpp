
#include "device.h"

#include <cstdint>
#include <cstring>
#include <cassert>
#include <new>

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

	program* program_create(
		const void* shader_code,
		uint32_t code_size)
	{
		assert(!!shader_code);
		assert(code_size != 0);

		program* prg = new(std::nothrow) program;

		if (!prg)
			return nullptr;

		prg->code = buffer_alloc(code_size);
		prg->uniforms = nullptr;
		prg->uniforms_size = 0;

		if (prg->code)
		{
			delete prg;
			return nullptr;
		}

		void* codeptr = mapmem(prg->code);
		memcpy(codeptr, shader_code, code_size);
		unmapmem(prg->code);

		return prg;
	}
	void program_delete(program* prg)
	{
		if (!prg)
			return;

		buffer_free(prg->code);
		buffer_free(prg->uniforms);

		delete prg;
	}

	void program_set_uniforms(
		program* prg,
		const void* uniforms,
		uint32_t uniform_buffer_size)
	{
		assert(!!prg && !!uniforms);
		assert(uniform_buffer_size != 0);

		if (!prg->uniforms)
		{
			prg->uniforms = buffer_alloc(uniform_buffer_size);
			prg->uniforms_size = uniform_buffer_size;
		}
		else if (prg->uniforms_size < uniform_buffer_size)
		{
			
		}

		buffer* buf = buffer_alloc(uniform_buffer_size);
		assert(!!buf);
		void* mapptr = mapmem(buf);
		memcpy(mapptr, uniforms, uniform_buffer_size);
		unmapmem(buf);

		prg->uniforms = buf;
	}
}
