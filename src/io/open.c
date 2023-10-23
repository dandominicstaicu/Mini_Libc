// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

int open(const char *filename, int flags, ...)
{
	va_list args;
	mode_t mode = 0;

	if (flags & O_CREAT) {
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
	}

	int ret = (int)syscall(__NR_open, filename, flags, mode);

	if (ret < 0) {
        errno = -ret;
        return -1;
    }

	return ret;
}
