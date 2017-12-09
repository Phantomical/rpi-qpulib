#pragma once
#pragma warning (disable : 4514)

#include <cstdlib>
#include <cstdint>

namespace qpu
{
	struct buffer;
	struct program;
	struct semaphore;

	enum buffer_flag : unsigned
	{
		BUF_FLAG_HINT_PERMAMAP = 1 << 0,
		BUF_FLAG_ZERO          = 1 << 2,
		BUF_FLAG_NO_INIT       = 1 << 3,
		BUF_FLAG_DIRECT        = 1 << 4,
		BUF_FLAG_COHERENT      = 1 << 5,

		BUF_FLAG_ALL           = ~0u,
	};

	enum init_err_code
	{
		INIT_SUCCESS = 0,
		INIT_ERR_ALREADY_INITIALIZED,
		INIT_ERR_MAILBOX_OPEN_FAILED,
		INIT_ERR_QPU_ENABLE_FAILED,
	};

	init_err_code init_qpu();
	void deinit_qpu();

	buffer* create_buffer(size_t size, buffer_flag flag);
	void delete_buffer(buffer*);

	//void buffer_data(
	//	buffer* buf, 
	//	const void* data,
	//	size_t size);

	void* buffer_map(buffer* buf);
	void buffer_unmap(buffer* buf);

	size_t buffer_size(const buffer* buf);

	program* create_program(
		const void* code,
		size_t program_size);
	void delete_program(
		program* prog);

	/* Queues a program for execution on
	   a QPU and sets up the uniform
	   buffer to be used by the program.

	   Modifying the buffer before the
	   program invocation has finished
	   running is undefined behaviour!

	   Parameters:
	   prog: The program that will be run.
	   uniforms: The buffer containing
	         the uniforms to be passed to
	         the program.

	   Returns:
	      A semaphore that is signalled
	      when program execution has
	      completed.	
	*/
	semaphore* run_program(
		program* prog,
		buffer* uniforms);

	//semaphore* create_semaphore();
	void delete_semaphore(semaphore*);

	/* Checks whether a semaphore is set */
	bool semaphore_is_set(semaphore*);

	/* Pushes program invocations onto the device
	   queue until the device queue is full.

	   Returns: true if there are still program
	            invocations that are queued.
	*/
	bool flush_queue();

	/* Waits for either the semaphore to be signaled
	   or for the timeout period to elapse.

	   Parameters:
	   sema:    The semaphore
	   timeout: Timeout in nanoseconds, or 0xFFFFFFFF
	            to wait forever.
	   
	   Returns: true if the semaphore was signaled, 
	            false otherwise.
	*/
	bool semaphore_wait(
		semaphore* sema,
		uint32_t timeout);
}

