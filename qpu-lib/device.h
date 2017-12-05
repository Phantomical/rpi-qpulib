#pragma once
#pragma warning (disable : 4514)

#include <memory>

namespace qpu
{
	struct semaphore;
	struct program;
	struct buffer;

	program* program_create(
		const void* shader_code,
		uint32_t code_size);
	void program_delete(program* prg);

	void program_set_uniforms(
		program* prg,
		const void* uniforms,
		uint32_t uniform_buffer_size);
	semaphore* program_run(program* prg);
	
	semaphore* semaphore_create();
	void semaphore_delete(semaphore* sema);
	
	bool semaphore_is_set(semaphore* sema);
	void semaphore_reset(semaphore* sema);

	buffer* buffer_alloc(uint32_t size);
	void buffer_free(buffer* buf);

	uint32_t buffer_gpu_ptr(buffer* buf);

	void* mapmem(buffer* buf);
	void unmapmem(buffer* buf);
}

namespace qpuxx
{
	class semaphore
	{
	private:
		std::unique_ptr<qpu::semaphore, void(*)(qpu::semaphore*)> sema;
		
	public:
		semaphore() :
			sema(qpu::semaphore_create(), &qpu::semaphore_delete)
		{

		}
		semaphore(qpu::semaphore* sema) :
			sema(sema, &qpu::semaphore_delete)
		{

		}
		semaphore(semaphore&& o) :
			sema(std::move(o.sema))
		{

		}

		semaphore& operator=(semaphore&& o)
		{
			sema = std::move(o.sema);
			return *this;
		}

		bool is_set() const
		{
			return qpu::semaphore_is_set(sema.get());
		}
		void reset()
		{
			qpu::semaphore_reset(sema.get());
		}

		qpu::semaphore* get()
		{
			return sema.get();
		}
	};
	class program
	{
	private:
		std::unique_ptr<qpu::program, void(*)(qpu::program*)> prg;

	public:
		program(const void* shader_code, uint32_t shader_size) :
			prg(qpu::program_create(shader_code, shader_size),
				&qpu::program_delete)
		{

		}
		program(qpu::program* prog) :
			prg(prog, &qpu::program_delete)
		{

		}
		program(program&& o) :
			prg(std::move(o.prg))
		{

		}

		program& operator=(program&& o)
		{
			prg = std::move(o.prg);
			return *this;
		}

		void set_uniforms(
			const void* uniforms,
			uint32_t uniform_buffer_size)
		{
			qpu::program_set_uniforms(
				prg.get(),
				uniforms,
				uniform_buffer_size);
		}
		semaphore run() const
		{
			return semaphore(qpu::program_run(prg.get()));
		}
	};
	class buffer
	{
	private:
		std::unique_ptr<qpu::buffer, void(*)(qpu::buffer*)> buf;

	public:
		buffer(uint32_t size) :
			buf(qpu::buffer_alloc(size), &qpu::buffer_free)
		{

		}
		buffer(qpu::buffer* bufptr) :
			buf(bufptr, &qpu::buffer_free)
		{

		}
		buffer(buffer&& o) :
			buf(std::move(o.buf))
		{

		}

		buffer& operator=(buffer&& o)
		{
			buf = std::move(o.buf);
			return *this;
		}

		void* map()
		{
			return qpu::mapmem(buf.get());
		}
		void unmap()
		{
			return qpu::unmapmem(buf.get());
		}
	};
}
