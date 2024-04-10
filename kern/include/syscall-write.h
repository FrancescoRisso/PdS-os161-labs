#ifndef _WRITE_H_
#define _WRITE_H_

#include <__includeTypes.h>

#include "kern/unistd.h"
#include "lib.h"
#include "opt-syscall_write.h"


#if OPT_SYSCALL_WRITE
int syscall_write(int fileDescriptor, userptr_t buffer, size_t size);
#endif

#endif
