// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	/* validate path and buf exist */
	if (!path || !buf) {
		errno = EINVAL;
		return -1;
	}

	/* check if the given path exists */
	if (syscall(__NR_access, path, F_OK) < 0) {
		errno = ENOENT;
		return -1;
	}

	int result = syscall(__NR_stat, path, buf);

	if (result < 0) {
		errno = -result;
		return -1;
	}

	return result;
}
