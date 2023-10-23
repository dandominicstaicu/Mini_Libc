#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <internal/syscall.h>


int nanosleep(const struct timespec *req, struct timespec *rem)
{
    if (!req || req->tv_nsec < 0 || req->tv_nsec >= 1000000000) {
        errno = EINVAL;
        return -1;
    }

    int result = syscall(__NR_nanosleep, req, rem);

    if (result < 0) {
        errno = -result;
    }

    return result;
}

unsigned int sleep(unsigned int seconds) {
    struct timespec req, rem;

    req.tv_sec = seconds;
    req.tv_nsec = 0;  // no additional nanoseconds

    if (nanosleep(&req, &rem) == -1) {
        if (errno == EINTR) {
            // sleep was interrupted by a signal
            return rem.tv_sec;
        }
    }
    return 0;  // successfully slept the entire interval
}
