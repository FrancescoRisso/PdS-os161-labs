#include <spinlock.h>

#include "opt-lock_with_sems.h"

#if !OPT_LOCK_WITH_SEMS

struct lock {
	char *lk_name;
	HANGMAN_LOCKABLE(lk_hangman); /* Deadlock detector hook. */
								  // add what you need here
								  // (don't forget to mark things volatile as needed)
};

#endif
