// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int truncate(const char *path, off_t length)
{
	if (!path || length < 0) {
		errno = EINVAL;
		return -1;
	}

	struct stat st;
	if (syscall(__NR_stat, path, &st) < 0) {
		errno = ENOENT;
		return -1;
	}

	if ((st.st_mode & __S_IFMT) == __S_IFDIR) {
		errno = EISDIR;
		return -1;
	}

	int result = syscall(__NR_truncate, path, length);

	if (result < 0) {
		errno = -result;
	}

	return result;
}
