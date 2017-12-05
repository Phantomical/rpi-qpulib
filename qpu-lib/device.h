
#include <memory>

namespace qpu
{
	struct semaphore;
	struct program;
	struct buffer;

	program* program_create(
		const void* shader_code,
		size_t code_size);
	void program_delete(program* prg);

	void program_set_uniforms(
		program* prg,
		const void* uniforms,
		size_t uniform_buffer_size);


	semaphore* semaphore_create();
	void semaphore_delete(semaphore* sema);
	
	bool semaphore_is_set(semaphore* sema);
	void semaphore_reset(semaphore* sema);

	buffer* buffer_alloc(size_t size);
	void buffer_free(buffer* buf);

	void* map(buffer* buf);
	void unmap(buffer* buf);
}

namespace qpuxx
{
	class semaphore
	{
	private:
		std::unique_ptr<qpu::semaphore, void(*)(qpu::semaphore*)> sema;
		
	public:
		semaphore() :
			sema(qpu::create_semaphore(), &qpu::delete_semaphore)
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
	};
}
