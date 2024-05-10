#include <__includeTypes.h>
#include <lib.h>
#include <synch.h>

#include "opt-lock_with_sems.h"
#include "opt-lock_with_wchans.h"


#if !OPT_LOCK_WITH_SEMS
#if !OPT_LOCK_WITH_WCHANS


struct lock *lock_create(const char *name) {
	struct lock *lock;

	lock = kmalloc(sizeof(*lock));
	if(lock == NULL) { return NULL; }

	lock->lk_name = kstrdup(name);
	if(lock->lk_name == NULL) {
		kfree(lock);
		return NULL;
	}

	HANGMAN_LOCKABLEINIT(&lock->lk_hangman, lock->lk_name);

	// add stuff here as needed

	return lock;
}

void lock_destroy(struct lock *lock) {
	KASSERT(lock != NULL);

	// add stuff here as needed

	kfree(lock->lk_name);
	kfree(lock);
}

void lock_acquire(struct lock *lock) {
	/* Call this (atomically) before waiting for a lock */
	// HANGMAN_WAIT(&curthread->t_hangman, &lock->lk_hangman);

	// Write this

	(void) lock;  // suppress warning until code gets written

	/* Call this (atomically) once the lock is acquired */
	// HANGMAN_ACQUIRE(&curthread->t_hangman, &lock->lk_hangman);
}

void lock_release(struct lock *lock) {
	/* Call this (atomically) when the lock is released */
	// HANGMAN_RELEASE(&curthread->t_hangman, &lock->lk_hangman);

	// Write this

	(void) lock;  // suppress warning until code gets written
}

bool lock_do_i_hold(struct lock *lock) {
	// Write this

	(void) lock;  // suppress warning until code gets written

	return true;  // dummy until code gets written
}

#endif
#endif
