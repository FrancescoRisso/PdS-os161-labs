#ifndef _LOCK_WITH_WCHAN_STRUCT
#define _LOCK_WITH_WCHAN_STRUCT

#include <current.h>
#include <spinlock.h>
#include <wchan.h>

#include "opt-lock_with_wchans.h"

#if OPT_LOCK_WITH_WCHANS

struct lock {
	char *lk_name;
	struct wchan *wc;
	struct thread *owner;
	struct spinlock internal_lock;
	HANGMAN_LOCKABLE(lk_hangman); /* Deadlock detector hook. */
};

#endif
#endif
