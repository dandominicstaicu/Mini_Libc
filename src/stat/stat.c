// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	if (!path || !buf) {
		errno = EINVAL;
		return -1;
	}

	if (syscall(__NR_access, path, F_OK) < 0) {
		errno = ENOENT;
		return -1;
	}

	int result = syscall(__NR_stat, path, buf);

	if (result < 0) {
		errno = -result;
	}

	return result;
}
