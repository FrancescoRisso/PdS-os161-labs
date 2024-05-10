#include "opt-cond_var.h"

#if OPT_COND_VAR

#include <__includeTypes.h>
#include <lib.h>
#include <synch.h>


struct cv *cv_free(struct cv *cv);


struct cv *cv_free(struct cv *cv) {
	if(cv->cv_name != NULL) kfree(cv->cv_name);
	if(cv->wc != NULL) wchan_destroy(cv->wc);
	spinlock_cleanup(&cv->internal_lock);
	kfree(cv);
	return NULL;
}


struct cv *cv_create(const char *name) {
	struct cv *cv;

	cv = kmalloc(sizeof(*cv));
	if(cv == NULL) return NULL;

	cv->cv_name = NULL;
	cv->wc = NULL;
	spinlock_init(&cv->internal_lock);

	if((cv->cv_name = kstrdup(name)) == NULL) return cv_free(cv);
	if((cv->wc = wchan_create(name)) == NULL) return cv_free(cv);

	return cv;
}

void cv_destroy(struct cv *cv) {
	KASSERT(cv != NULL);
	cv_free(cv);
}

void cv_wait(struct cv *cv, struct lock *lock) {
	KASSERT(lock != NULL);
	KASSERT(cv != NULL);
	KASSERT(lock_do_i_hold(lock));

	spinlock_acquire(&cv->internal_lock);

	lock_release(lock);
	wchan_sleep(cv->wc, &cv->internal_lock);
	spinlock_release(&cv->internal_lock);

	lock_acquire(lock);
}
#include <cpu.h>

void cv_signal(struct cv *cv, struct lock *lock) {
	KASSERT(lock != NULL);
	KASSERT(cv != NULL);
	KASSERT(lock_do_i_hold(lock));
	
	spinlock_acquire(&cv->internal_lock);
	wchan_wakeone(cv->wc, &cv->internal_lock);
	spinlock_release(&cv->internal_lock);
}

void cv_broadcast(struct cv *cv, struct lock *lock) {
	KASSERT(lock != NULL);
	KASSERT(cv != NULL);
	KASSERT(lock_do_i_hold(lock));
	
	spinlock_acquire(&cv->internal_lock);
	wchan_wakeall(cv->wc, &cv->internal_lock);
	spinlock_release(&cv->internal_lock);
}

#endif
