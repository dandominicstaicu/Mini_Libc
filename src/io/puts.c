#include <stdio.h>
#include <string.h>
#include <unistd.h>

int puts(const char *str)
{
    const char newline = '\n';

    if (write(STDOUT_FILENO, str, strlen(str)) < 0)
        return EOF;

    if (write(STDOUT_FILENO, &newline, 1) < 0)
        return EOF;

    return 1;
}
