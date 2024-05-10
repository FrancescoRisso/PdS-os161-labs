#include <__includeTypes.h>
#include <lib.h>
#include <my-synch/lock-with-semaphores-struct.h>
#include <synch.h>

#include "opt-lock_with_sems.h"


#if OPT_LOCK_WITH_SEMS


struct lock *lock_free(struct lock *lock);


struct lock *lock_free(struct lock *lock) {
	if(lock->lk_name != NULL) kfree(lock->lk_name);
	if(lock->sem != NULL) sem_destroy(lock->sem);
	kfree(lock);
	return NULL;
}


struct lock *lock_create(const char *name) {
	struct lock *lock;

	lock = kmalloc(sizeof(*lock));
	if(lock == NULL) return NULL;

	lock->lk_name = NULL;
	lock->owner = NULL;
	lock->sem = NULL;

	if((lock->lk_name = kstrdup(name)) == NULL) return lock_free(lock);

	HANGMAN_LOCKABLEINIT(&lock->lk_hangman, lock->lk_name);

	if((lock->sem = sem_create(name, 1)) == NULL) return lock_free(lock);

	spinlock_init(&lock->internal_lock);

	return lock;
}

void lock_destroy(struct lock *lock) {
	KASSERT(lock != NULL);
	lock_free(lock);
}

void lock_acquire(struct lock *lock) {
	HANGMAN_WAIT(&curthread->t_hangman, &lock->lk_hangman);

	P(lock->sem);
	lock->owner = curthread;

	HANGMAN_ACQUIRE(&curthread->t_hangman, &lock->lk_hangman);
}

void lock_release(struct lock *lock) {
	HANGMAN_RELEASE(&curthread->t_hangman, &lock->lk_hangman);

	spinlock_acquire(&lock->internal_lock);
	KASSERT(lock->owner == curthread);
	lock->owner = NULL;
	V(lock->sem);
	spinlock_release(&lock->internal_lock);
}

bool lock_do_i_hold(struct lock *lock) {
	return lock->owner == curthread;
}

#endif
