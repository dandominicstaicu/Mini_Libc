// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/types.h>
#include <fcntl.h>

// The lseek function repositions the file offset of the open file description
// associated with the file descriptor `fd` to the argument `offset` based on the `whence` directive.
off_t lseek(int fd, off_t offset, int whence)
{
    // Check if the file descriptor (fd) is valid. File descriptors are non-negative integers.
    if (fd < 0) {
        errno = EBADF;  // Set errno to indicate a bad file descriptor.
        return -1;
    }

    // Validate the whence parameter. It should be one of SEEK_SET, SEEK_CUR, or SEEK_END.
    if (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END) {
        errno = EINVAL;  // Set errno to indicate an invalid argument.
        return -1;
    }

    // Check for an invalid negative offset when whence is SEEK_CUR.
    // In this mode, a negative offset would attempt to move the file pointer backwards.
    if (offset < 0 && whence == SEEK_CUR) {
        errno = EINVAL;  // Set errno to indicate an invalid argument.
        return -1;
    }

    // Check for an invalid negative offset when whence is SEEK_SET.
    // In SEEK_SET mode, the offset sets the position relative to the beginning of the file.
    if (whence == SEEK_SET && offset < 0) {
        errno = EINVAL;  // Set errno to indicate an invalid argument for SEEK_SET with a negative offset.
        return -1;
    }

    // Invoke the lseek system call using the provided fd, offset, and whence.
    off_t result = (off_t) syscall(__NR_lseek, fd, offset, whence);

    // Check the result of the system call. If it returns -1, an error occurred.
    if (result == (off_t) -1) {
        errno = -result;  // Set errno based on the returned error code.
    }

    // Return the result of the lseek system call, which is the new file offset.
    return result;
}
