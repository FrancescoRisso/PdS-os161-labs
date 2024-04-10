#include "hello.h"

#include <clock.h>
#include <current.h>
#include <device.h>
#include <kern/errno.h>
#include <kern/reboot.h>
#include <kern/unistd.h>
#include <lib.h>
#include <mainbus.h>
#include <proc.h>
#include <spl.h>
#include <synch.h>
#include <syscall.h>
#include <test.h>
#include <thread.h>
#include <types.h>
#include <version.h>
#include <vfs.h>
#include <vm.h>

#include "autoconf.h"  // for pseudoconfig

#if OPT_HELLO
void printHello(void) {
	kprintf(" ___________________________\n");
	kprintf("|                           |\n");
	kprintf("|        Hello World!       |\n");
	kprintf("|___________________________|\n");
	kprintf("\n");
}
#endif
