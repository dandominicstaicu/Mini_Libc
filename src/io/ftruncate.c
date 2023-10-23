// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int ftruncate(int fd, off_t length)
{
	if (length < 0) {
		errno = EINVAL;
		return -1;
	}

	if (fd < 0) {
		errno = EBADF;
		return -1;
	}

	struct stat st;
	if (fstat(fd, &st) < 0) {
		errno = EINVAL;
		return -1;
	}

	if ((st.st_mode & __S_IFMT) == __S_IFDIR) {
		errno = EINVAL;
		return -1;
	}

	// Attempt a zero-byte write to check if fd is writable
    if (write(fd, NULL, 0) < 0) {
        errno = EBADF;  // Bad file descriptor (not writable)
        return -1;
    }

	int result = syscall(__NR_ftruncate, fd, length);

	if (result < 0) {
		errno = -result;
	}

	return result;
}
