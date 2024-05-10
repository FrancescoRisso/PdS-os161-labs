#include <__includeTypes.h>
#include <lib.h>
#include <my-synch/lock-with-wchan-struct.h>
#include <synch.h>

#include "opt-lock_with_wchans.h"


#if OPT_LOCK_WITH_WCHANS


struct lock *lock_free(struct lock *lock);


struct lock *lock_free(struct lock *lock) {
	if(lock->lk_name != NULL) kfree(lock->lk_name);
	if(lock->wc != NULL) wchan_destroy(lock->wc);
	kfree(lock);
	return NULL;
}


struct lock *lock_create(const char *name) {
	struct lock *lock;

	lock = kmalloc(sizeof(*lock));
	if(lock == NULL) return NULL;

	lock->lk_name = NULL;
	lock->owner = NULL;
	lock->wc = NULL;

	if((lock->lk_name = kstrdup(name)) == NULL) return lock_free(lock);

	HANGMAN_LOCKABLEINIT(&lock->lk_hangman, lock->lk_name);

	if((lock->wc = wchan_create(name)) == NULL) return lock_free(lock);

	spinlock_init(&lock->internal_lock);

	return lock;
}

void lock_destroy(struct lock *lock) {
	KASSERT(lock != NULL);
	lock_free(lock);
}

void lock_acquire(struct lock *lock) {
	HANGMAN_WAIT(&curthread->t_hangman, &lock->lk_hangman);

	spinlock_acquire(&lock->internal_lock);

	while(lock->owner != NULL) wchan_sleep(lock->wc, &lock->internal_lock);

	lock->owner = curthread;
	spinlock_release(&lock->internal_lock);

	HANGMAN_ACQUIRE(&curthread->t_hangman, &lock->lk_hangman);
}

void lock_release(struct lock *lock) {
	HANGMAN_RELEASE(&curthread->t_hangman, &lock->lk_hangman);

	spinlock_acquire(&lock->internal_lock);

	KASSERT(lock->owner == curthread);

	lock->owner = NULL;
	wchan_wakeall(lock->wc, &lock->internal_lock);

	spinlock_release(&lock->internal_lock);
}

bool lock_do_i_hold(struct lock *lock) {
	return lock->owner == curthread;
}

#endif
