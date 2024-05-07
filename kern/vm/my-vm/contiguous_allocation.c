#include "contiguous_allocation.h"

#if OPT_CONTIGUOUS_ALLOCATION

static struct spinlock allocmem_lock = SPINLOCK_INITIALIZER;
// static struct spinlock freemem_lock = SPINLOCK_INITIALIZER;

#define page2addr(p) baseAddr + p *PAGE_SIZE

static short *pages;  // -1 if free, otherwhise index of first page in allocation block
static int numPages = 0;
static paddr_t baseAddr;
static bool initialized = false;

#define TEST_print_pages()                                       \
	kprintf("[ ");                                               \
	for(int i = 0; i < numPages; i++) kprintf("%d, ", pages[i]); \
	kprintf("]\n")

/*
	find_allocation_spot
	------------------------------------------------------------------
	Finds the smallest contiguous set of at least allocSize blocks
	------------------------------------------------------------------
	PARAMETERS:
		- allocSize: the number of desired blocks
	------------------------------------------------------------------
	OUTPUT:
		- the index of the first block to be allocated, if found
		- -1 otherwise
*/
int find_allocation_spot(unsigned allocSize);


int find_allocation_spot(unsigned allocSize) {
	unsigned size = 0;
	unsigned minSize = (unsigned) -1;
	int block_minSize = -1;

	for(int i = 0; i <= numPages; i++) {
		if(i < numPages && pages[i] == -1)
			size++;
		else if(size != 0 && size < minSize && size >= allocSize) {
			minSize = size;
			block_minSize = i - size;
			size = 0;
		}
	}

	return block_minSize;
}

void vm_bootstrap(void) {
	numPages = 0;
	for(baseAddr = ram_stealmem(1); ram_stealmem(1) != 0;) numPages++;

	pages = kmalloc(numPages * sizeof(short));
	for(int page = 0; page < numPages; page++) pages[page] = -1;

	initialized = true;
}

vaddr_t alloc_kpages(unsigned npages) {
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
	paddr_t addr;

	spinlock_acquire(&allocmem_lock);

	kprintf("\t%ld pages requested\n", npages);

	if(!initialized)
		addr = ram_stealmem(npages);
	else {
		int page = find_allocation_spot(npages);
		
		if(page == -1) addr = 0;

		for(unsigned i = 0; i < npages; i++) pages[page + i] = page;
		addr = page2addr(page);
	}

	spinlock_release(&allocmem_lock);

	return addr;
}

#endif
