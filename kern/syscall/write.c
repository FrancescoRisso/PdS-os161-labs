#include "syscall-write.h"

#if OPT_SYSCALL_WRITE

int syscall_write(int fileDescriptor, userptr_t buffer, size_t size) {
	if(fileDescriptor != STDOUT_FILENO && fileDescriptor != STDERR_FILENO) {
		kprintf("Only writes to stdout and stderr are supported");
		return -1;
	}

	char* string = (char*) buffer;

	unsigned i;
	for(i = 0; i < size && string[i] != '\0'; i++) putch(string[i]);

	return i;
}

#endif
