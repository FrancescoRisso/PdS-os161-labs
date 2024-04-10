#include "syscall-exit.h"

#if OPT_SYSCALL_EXIT

void syscall_exit(int code) {
	struct addrspace *addressSpace = proc_getas();
	as_destroy(addressSpace);
	thread_exit();
	panic("thread_exit returned (this should never happen)\n");
	(void) code;
}

#endif
