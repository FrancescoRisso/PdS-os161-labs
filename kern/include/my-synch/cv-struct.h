#ifndef _CV_STRUCT
#define _CV_STRUCT

#include "opt-cond_var.h"

#if OPT_COND_VAR

#include <current.h>
#include <wchan.h>

struct cv {
	char *cv_name;
	struct wchan *wc;
	struct spinlock internal_lock;
};

#endif
#endif
