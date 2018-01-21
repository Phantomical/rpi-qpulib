
#include "qpulib.h"

#include <memory>

namespace qpuxx
{
	class buffer
	{
	private:
		std::shared_ptr<qpu::buffer> buf;

	public:
		buffer() :
			buf(nullptr)
		{

		}
		buffer(qpu::buffer* bufptr) :
			buf(bufptr, &qpu::delete_buffer)
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
			return qpu::buffer_map(buf.get());
		}
		void unmap()
		{
			return qpu::buffer_unmap(buf.get());
		}

		operator bool() const
		{
			return buf.get();
		}
		qpu::buffer* get()
		{
			return buf.get();
		}
		size_t size() const
		{
			return qpu::buffer_size(buf.get());
		}
	};

	class semaphore
	{
	private:
		std::unique_ptr<qpu::semaphore, void(*)(qpu::semaphore*)> sema;

	public:
		semaphore(qpu::semaphore* sema) :
			sema(sema, &qpu::delete_semaphore)
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
		qpu::semaphore* get()
		{
			return sema.get();
		}
	};
	class program
	{
	private:
		std::shared_ptr<qpu::program> prg;

	public:
		program(const void* shader_code, uint32_t shader_size) :
			prg(qpu::create_program(shader_code, shader_size),
				&qpu::delete_program)
		{

		}
		program(qpu::program* prog) :
			prg(prog, &qpu::delete_program)
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

		semaphore run(buffer uniforms) const
		{
			return semaphore(qpu::run_program(
				prg.get(),
				uniforms.get()));
		}

		qpu::program* get()
		{
			return prg.get();
		}
	};
}
