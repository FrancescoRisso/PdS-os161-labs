#ifndef _LOCK_WITH_SEM_STRUCT
#define _LOCK_WITH_SEM_STRUCT

#include <spinlock.h>

#include "opt-lock_with_sems.h"

#if OPT_LOCK_WITH_SEMS

#include "current.h"
#include "synch.h"

struct lock {
	char *lk_name;
	struct semaphore *sem;
	struct thread *owner;
	struct spinlock internal_lock;
	HANGMAN_LOCKABLE(lk_hangman); /* Deadlock detector hook. */
};

#endif
#endif
