
#include "qpulib.h"
#include "registers.h"
#include "device.h"

#include <new>
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

	init_err_code init_qpu()
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

		// If this assertion fires, then most likely
		// the same buffer has been deleted multiple
		// times.
		assert(it->second != 0);

		if (--it->second == 0)
		{
			//
			delete_buffer_impl(buf);

			buffer_refcounts.erase(it);
		}
	}

}
