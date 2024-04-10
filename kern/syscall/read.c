#include "syscall-read.h"

#if OPT_SYSCALL_READ

int syscall_read(int fileDescriptor, userptr_t buffer, size_t size) {
	if(fileDescriptor != STDIN_FILENO) {
		kprintf("Only reads from stdin are supported");
		return -1;
	}

	char* string = (char*) buffer;
	int read;

	unsigned i;
	for(i = 0; i < size - 1; i++) {
		if((read = getch()) >= 0)
			string[i++] = read;
		else
			break;
	}

	string[i] = '\0';

	return i;
}

#endif
