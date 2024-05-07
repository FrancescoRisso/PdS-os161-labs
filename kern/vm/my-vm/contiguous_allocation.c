#include "contiguous_allocation.h"

#if OPT_CONTIGUOUS_ALLOCATION

static struct spinlock allocmem_lock = SPINLOCK_INITIALIZER;
// static struct spinlock freemem_lock = SPINLOCK_INITIALIZER;

static short *pages;  // -1 if free, otherwhise index of first page in allocation block
static int numPages = 0;
static paddr_t baseAddr;

void vm_bootstrap(void) {
	numPages = 0;
	for(baseAddr = ram_stealmem(1); ram_stealmem(1) != 0;) numPages++;

	pages = kmalloc(numPages * sizeof(short));
	for(int page = 0; page < numPages; page++) pages[page] = -1;
}

vaddr_t alloc_kpages(unsigned npages) {
	// npages++;            // TODO
	// return (vaddr_t) 0;  // TODO

	paddr_t pa;

	// dumbvm_can_sleep();
	pa = getppages(npages);
	if(pa == 0) { return 0; }
	return PADDR_TO_KVADDR(pa);
}

void free_kpages(vaddr_t addr) {
	addr++;  // TODO
}

paddr_t getppages(unsigned long npages) {
	// npages++;  // TODO
	// return 0;  // TODO

	paddr_t addr;

	spinlock_acquire(&allocmem_lock);

	addr = ram_stealmem(npages);

	spinlock_release(&allocmem_lock);
	return addr;
}

#endif
