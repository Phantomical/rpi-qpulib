
#include "qpulib.h"
#include "device.h"
#include "mailbox.h"

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
	}

	buffer* create_buffer(size_t size, buffer_flag flag)
	{
		if (!qpu_device)
			return nullptr;

	
	}
}
