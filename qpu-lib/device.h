
#include "mailbox.h"
#include "qpulib.h"

#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace qpu
{
	struct buffer
	{
		uint32_t handle;
		uint32_t bus_addr;
		uint32_t size;
		void* map_ptr;

		~buffer();
	};

	struct program
	{
		buffer* code_buf;
	};

	struct semaphore
	{
		// TODO: Trigger this from 
		// the QPU, instead of just
		// polling until finished
		bool is_finished;

		std::function<void()> cleanup_func;
	};

	class device
	{
	private:
		int mailbox;

		std::unordered_map<program*, uint32_t> program_refcounts;
		std::unordered_map<buffer*, uint32_t> buffer_refcounts;		
		std::unordered_set<semaphore*> inactive_semaphores;

		friend enum init_err_code init_qpu();

		device() = default;
		device(const device&) = delete;
		device(device&&) = delete;
		void operator=(const device&) = delete;
		void operator=(device&&) = delete;

		void delete_buffer_impl(buffer* buf);
		void delete_program_impl(program* prog);

	public:
		~device();

		void free_unreferenced();

		buffer* create_buffer(uint32_t size, buffer_flag flags);
		void delete_buffer(buffer* buf);

		void* buffer_map(buffer* buf);
		void buffer_unmap(buffer* buf);

		program* create_program(
			const void* code,
			uint32_t program_size);
		void delete_program(program* prog);

		semaphore* run_program(
			program* prog,
			buffer* buf);

		void delete_semaphore(semaphore*);
	};
}
