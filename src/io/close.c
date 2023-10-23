// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	/* syscall close and store ret value */
	int ret = syscall(__NR_close, fd);

	/* check if system call failed */
	if (ret < 0) {
		/* if an error occured, set errno and return -1 */
		errno = -ret;
		return -1;
	}

	return ret;
}
