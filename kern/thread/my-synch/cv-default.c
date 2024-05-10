#include "opt-cond_var.h"

#if !OPT_COND_VAR

#include <__includeTypes.h>
#include <lib.h>
#include <synch.h>

struct cv *cv_create(const char *name) {
	struct cv *cv;

	cv = kmalloc(sizeof(*cv));
	if(cv == NULL) { return NULL; }

	cv->cv_name = kstrdup(name);
	if(cv->cv_name == NULL) {
		kfree(cv);
		return NULL;
	}

	// add stuff here as needed

	return cv;
}

void cv_destroy(struct cv *cv) {
	KASSERT(cv != NULL);

	// add stuff here as needed

	kfree(cv->cv_name);
	kfree(cv);
}

void cv_wait(struct cv *cv, struct lock *lock) {
	// Write this
	(void) cv;    // suppress warning until code gets written
	(void) lock;  // suppress warning until code gets written
}

void cv_signal(struct cv *cv, struct lock *lock) {
	// Write this
	(void) cv;    // suppress warning until code gets written
	(void) lock;  // suppress warning until code gets written
}

void cv_broadcast(struct cv *cv, struct lock *lock) {
	// Write this
	(void) cv;    // suppress warning until code gets written
	(void) lock;  // suppress warning until code gets written
}

#endif
