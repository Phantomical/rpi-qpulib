
#include "qpulib.h"
#include "device.h"
#include "mailbox.h"

#include <chrono>

namespace qpu
{
	static device* qpu_device = nullptr;

	init_err_code init_qpu(unsigned num_qpus)
	{
		if (qpu_device)
			return INIT_ERR_ALREADY_INITIALIZED;

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
		qpu_device = nullptr;
	}

	buffer* create_buffer(uint32_t size, buffer_flag flag)
	{
		if (!qpu_device)
			return nullptr;

		if (size == 0)
			return nullptr;

		return qpu_device->create_buffer(size, flag);
	}
	void delete_buffer(buffer* buf)
	{
		if (!qpu_device || !buf)
			return;

		qpu_device->delete_buffer(buf);
	}

	void* buffer_map(buffer* buf)
	{
		if (!qpu_device || !buf)
			return nullptr;

		return qpu_device->buffer_map(buf);
	}
	void buffer_unmap(buffer* buf)
	{
		if (!qpu_device || !buf)
			return;

		qpu_device->buffer_unmap(buf);
	}

	size_t buffer_size(const buffer* buf)
	{
		if (!buf)
			return 0;

		return buf->size;
	}

	program* create_program(
		const void* code,
		uint32_t program_size)
	{
		if (!code || !qpu_device || program_size == 0)
			return nullptr;

		return qpu_device->create_program(code, program_size);
	}
	void delete_program(
		program* prog)
	{
		if (!prog || !qpu_device)
			return;

		qpu_device->delete_program(prog);
	}

	semaphore* run_program(
		program* prog,
		buffer* uniforms)
	{
		if (!prog || !qpu_device)
			return nullptr;

		return qpu_device->run_program(prog, uniforms);
	}

	void delete_semaphore(semaphore* sema)
	{
		if (!sema || !qpu_device)
			return;

		qpu_device->delete_semaphore(sema);
	}

	bool semaphore_is_set(semaphore* sema)
	{
		if (!sema || !qpu_device)
			return false;

		return sema->is_finished;
	}
	bool semaphore_wait(semaphore* sema, uint32_t timeout)
	{
		if (!sema || !qpu_device)
			return false;

		auto stop_time = std::chrono::high_resolution_clock::now()
			+ std::chrono::nanoseconds(timeout);

		while (!sema->is_finished)
		{
			qpu_device->do_gc();

			if (timeout != NO_TIMEOUT && 
				stop_time > std::chrono::high_resolution_clock::now())
			{
				return false;
			}
		}

		return true;
	}
}
