#ifndef _CV_DEFAULT_STRUCT
#define _CV_DEFAULT_STRUCT

#include "opt-cond_var.h"

#if !OPT_COND_VAR

struct cv {
	char *cv_name;
	// add what you need here
	// (don't forget to mark things volatile as needed)
};

#endif
#endif
