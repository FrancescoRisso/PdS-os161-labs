#ifndef _LOCK_DEFAULT_STRUCT
#define _LOCK_DEFAULT_STRUCT

#include <spinlock.h>

#include "opt-lock_with_sems.h"
#include "opt-lock_with_wchans.h"

#if !OPT_LOCK_WITH_SEMS
#if !OPT_LOCK_WITH_WCHANS

struct lock {
	char *lk_name;
	HANGMAN_LOCKABLE(lk_hangman); /* Deadlock detector hook. */
								  // add what you need here
								  // (don't forget to mark things volatile as needed)
};

#endif
#endif
#endif
