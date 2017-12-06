#pragma once
#pragma warning (disable : 4514)

#include <memory>

namespace qpu
{
	struct buffer;
	struct program;
	struct semaphore;

	buffer* create_buffer();
	void delete_buffer(buffer*);

	void buffer_data(
		buffer* buf, 
		const void* data,
		size_t size);

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

