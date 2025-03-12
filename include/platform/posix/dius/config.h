#pragma once

#include <dius/c_definitions.h>

// Clock nanosleep is controlled by this field of POSIX.
#if defined(_POSIX_CLOCK_SELECTION) && _POSIX_CLOCK_SELECTION >= 0
#define DIUS_HAVE_CLOCK_NANOSLEEP
#endif

// Most OSes don't like using mknod() to create regular files.
#undef DIUS_USE_MKNOD_TO_CREATE_FILES
