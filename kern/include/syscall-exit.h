#ifndef _EXIT_H_
#define _EXIT_H_

#include <__includeTypes.h>
#include <addrspace.h>
#include <lib.h>
#include <proc.h>
#include <thread.h>

#include "opt-syscall_exit.h"

#if OPT_SYSCALL_EXIT
void syscall_exit(int code);
#endif

#endif
