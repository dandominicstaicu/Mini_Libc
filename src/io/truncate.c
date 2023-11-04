// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int truncate(const char *path, off_t length)
{
	/* check if path exists and if size is valid */
	if (!path || length < 0) {
		errno = EINVAL;
		return -1;
	}

	/* get status of the file associated with fd */
	struct stat st;
	if (syscall(__NR_stat, path, &st) < 0) {
		errno = ENOENT; /* failed to get the status, file doesnt exist */
		return -1;
	}

	/* check if the given path exists */
	if (syscall(__NR_access, path, F_OK) < 0) {
		errno = ENOENT;
		return -1;
	}

	/* check if the file is a directory */
	if ((st.st_mode & __S_IFMT) == __S_IFDIR) {
		errno = EISDIR; /* file is a directory */
		return -1;
	}

	int result = syscall(__NR_truncate, path, length);

	if (result < 0) {
		errno = -result;
		return -1;
	}

	return result;
}
