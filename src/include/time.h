#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <internal/types.h>

#define __MAX_NSEC 999999999
#define __MIN_NSEC 0

/* used to represent time intervals in UNIX-like operating systems */
struct timespec {
    time_t tv_sec; //seconds
    long tv_nsec; //nanoseconds
};

int nanosleep(const struct timespec *req, struct timespec *rem);

unsigned int sleep(unsigned int seconds);

#ifdef __cplusplus
}
#endif

#endif
