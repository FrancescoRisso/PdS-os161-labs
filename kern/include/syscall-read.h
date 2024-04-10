#ifndef _READ_H_
#define _READ_H_

#include <__includeTypes.h>

#include "kern/unistd.h"
#include "lib.h"
#include "opt-syscall_read.h"


#if OPT_SYSCALL_READ
int syscall_read(int fileDescriptor, userptr_t buffer, size_t size);
#endif

#endif
