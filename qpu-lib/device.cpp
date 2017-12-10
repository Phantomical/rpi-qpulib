
#include "qpulib.h"
#include "device.h"
#include "mailbox.h"

#include <new>
#include <vector>
#include <cstring>
#include <cassert>

namespace qpu
{
	enum mem_alloc_flags : uint32_t
	{
		// Can be resized to 0 at any time. Use this for cached data.
		MEM_FLAG_DISCARDABLE    = 1 << 0,
		// Uncached memory
		MEM_FLAG_DIRECT         = 1 << 2,
		// Non-allocating in L2 but coherent
		MEM_FLAG_COHERENT       = 1 << 3,
		// Initialize buffer to zeros
		MEM_FLAG_ZERO           = 1 << 4,
		// Don't initialize
		MEM_FLAG_NO_INIT        = 1 << 5,
		// Likely to be locked for long periods of time
		MEM_FLAG_HINT_PERMALOCK = 1 << 6,
		// Allocating in L2
		MEM_FLAG_L1_NONALLOCATING = MEM_FLAG_DIRECT | MEM_FLAG_COHERENT
	};

	static constexpr uint32_t buf_align = 16;

	static device* qpu_device = nullptr;

	init_err_code init_qpu(unsigned num_qpus)
	{
		int mailbox = mbox_open();

		if (!mailbox)
			return INIT_ERR_MAILBOX_OPEN_FAILED;

		if (!qpu_enable(mailbox, 1))
		{
			mbox_close(mailbox);
			return INIT_ERR_QPU_ENABLE_FAILED;
		}

		device* d = new device;
		d->mailbox = mailbox;

		qpu_device = d;

		return INIT_SUCCESS;
	}
	void deinit_qpu()
	{
		delete qpu_device;
	}

	void device::delete_buffer_impl(buffer* buf)
	{
		assert(!!buf);

		if (buf->map_ptr)
			unmapmem(buf->map_ptr, buf->size);

		if (buf->bus_addr)
			mem_unlock(mailbox, buf->bus_addr);

		if (buf->handle)
			mem_free(mailbox, buf->handle);

		delete buf;
	}
	void device::delete_program_impl(program* prog)
	{
		assert(!!prog);

		delete_buffer(prog->code_buf);

		delete prog;
	}
	
	buffer* device::create_buffer(uint32_t size, buffer_flag flags)
	{
		if (size == 0)
			return nullptr;

		uint32_t handle = mem_alloc(
			mailbox,
			size,
			buf_align,
			MEM_FLAG_HINT_PERMALOCK | MEM_FLAG_NO_INIT);

		if (!handle)
			return nullptr;

		uint32_t buf_addr = mem_lock(mailbox, handle);

		if (!buf_addr)
		{
			mem_free(mailbox, handle);
			return nullptr;
		}

		buffer* buf = new (std::nothrow) buffer;
		if (!buf)
		{
			mem_unlock(mailbox, buf_addr);
			mem_free(mailbox, handle);

			return nullptr;
		}

		buf->handle = handle;
		buf->bus_addr = buf_addr;
		buf->size = size;
		buf->map_ptr = nullptr;

		buffer_refcounts.insert(std::make_pair(buf, (uint32_t)1));

		return buf;
	}
	void device::delete_buffer(buffer* buf)
	{
		// Null buffers shouldn't be passed to this 
		// function, they should have already been
		// dealt with by the public library function
		assert(buf);

		auto it = buffer_refcounts.find(buf);
		// The buffer must exist
		assert(it != buffer_refcounts.end());

		// If this assertion fires, then most likely
		// the same buffer has been deleted multiple
		// times.
		assert(it->second != 0);

		if (--it->second == 0)
		{
			// Delete the buffer
			delete_buffer_impl(buf);

			// Then remove it's counter entry
			buffer_refcounts.erase(it);
		}
	}

	void* device::buffer_map(buffer* buf)
	{
		// Null buffers should be dealt with
		// before this function is called
		assert(buf);

		// The handle should be valid always
		assert(buf->handle);

		// Same with the bus address
		assert(buf->bus_addr);

		// Size needs to be greater than 0
		assert(buf->size > 0);

		if (buf->map_ptr)
			return buf->map_ptr;

		buf->map_ptr = mapmem(buf->bus_addr, buf->size);

		return buf->map_ptr;
	}
	void device::buffer_unmap(buffer* buf)
	{
		// No null pointers should be 
		// passed to this method
		assert(buf);

		// The handle should always valid
		assert(buf->handle);

		// The buffer address should always be valid
		assert(buf->bus_addr);

		// If this assert fails then the most likely
		// cause is that the buffer has been freed
		// twice. One reason to check for is that
		// when a buffer that is mapped is mapped
		// again the same mapping is returned.
		assert(buf->map_ptr);

		unmapmem(buf->map_ptr, buf->size);
	}

	program* device::create_program(
		const void* code,
		uint32_t program_size)
	{
		if (!code || program_size == 0)
			return nullptr;

		buffer* code_buf = create_buffer(program_size, BUF_FLAG_NO_INIT);

		if (!code_buf)
			return nullptr;

		program* prog = new (std::nothrow) program;

		if (!prog)
		{
			delete_buffer(code_buf);
			return nullptr;
		}

		prog->code_buf = code_buf;

		void* mapptr = buffer_map(code_buf);
		if (!mapptr) // Abort if mapping failed
		{
			delete_program_impl(prog);
			return nullptr;
		}

		memcpy(mapptr, code, program_size);

		buffer_unmap(code_buf);

		program_refcounts.insert(std::make_pair(prog, (uint32_t)1));

		return prog;
	}
	void device::delete_program(program* prog)
	{
		// Null programs should not be passed to this function
		assert(prog);

		auto it = program_refcounts.find(prog);

		// The program must be in the reference counting list
		assert(it != program_refcounts.end());

		// Check for double frees
		assert(it->second != 0);

		if (--it->second == 0)
		{
			delete_program_impl(prog);

			program_refcounts.erase(it);
		}
	}

	void device::delete_semaphore(semaphore* sema)
	{
		assert(sema);

		if (!sema->is_finished)
			inactive_semaphores.insert(sema);
		else
			delete sema;
	}

	void device::do_gc()
	{
		std::vector<semaphore*> to_delete;

		for (auto sema : inactive_semaphores)
		{
			if (sema->is_finished)
				to_delete.push_back(sema);
		}

		for (auto to_del : to_delete)
		{
			auto it = inactive_semaphores.find(to_del);
			inactive_semaphores.erase(it);
		}
	}
}
