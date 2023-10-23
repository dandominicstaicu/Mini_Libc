#include <stdio.h>
#include <string.h>
#include <unistd.h>

int puts(const char *str)
{
    const char newline = '\n';

    /* Write the string to stdout and check if it's successfull */
    if (write(STDOUT_FILENO, str, strlen(str)) < 0)
        return EOF;

    /* Write a newline character to stdout after the string
    and check if it's successfull */
    if (write(STDOUT_FILENO, &newline, 1) < 0)
        return EOF;

    return 1;
}
