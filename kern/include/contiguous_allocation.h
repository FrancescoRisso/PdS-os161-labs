#ifndef _CONTIGUOUS_ALLOCATION_H_
#define _CONTIGUOUS_ALLOCATION_H_

#include <__includeTypes.h>
#include <lib.h>
#include <vm.h>

#include "opt-contiguous_allocation.h"
#include "spinlock.h"

paddr_t getppages(unsigned long npages);

#endif
