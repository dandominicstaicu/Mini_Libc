// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	// check for null pointers
	if (destination == NULL || source == NULL)
		return NULL;

	// copy the string
	char *tmp = destination;

	// loop through the string and copy it
	while ((*tmp = *source) != '\0') {
		tmp++;
		source++;
	}

	// return the destination
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	// check for null pointers
	if (destination == NULL || source == NULL)
		return NULL;

	// copy the string
	char *tmp = destination;

	// loop through the string and copy it until the length is reached
	while ((*tmp = *source) != '\0' && len-- > 0) {
		++tmp;
		++source;
	}

	// return the destination
	return destination;
}

char *strcat(char *destination, const char *source)
{
	// point to the end of the destination string
	char *ptr = destination + strlen(destination);

	// copy the source string to the end of the destination string
	while (*source != '\0') {
		*ptr++ = *source++;
	}

	// add null character at the end
	*ptr = '\0';


	// return the destination
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	// point to the end of the destination string
	char *ptr = destination + strlen(destination);

	// copy the source string to the end of the destination string until the length is reached
	while (*source != '\0' && len-- > 0) {
		*ptr++ = *source++;
	}

	// add null character at the end
	*ptr = '\0';

	// return the destination
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	// loop through the string while neither string reached the end of it
	while (*str1 != '\0' && *str2 != '\0') {
		// if current characters don't match
		if (*str1 != *str2)
			break;
			// return *str1 - *str2;

		str1++;
		str2++;
	}


	return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		if (str1[i] != str2[i]) {
			return (str1[i] < str2[i]) ? -1 : 1;
		}
		if (str1[i] == '\0') {
			return 0;
		}
	}
	return 0;
}
// int strncmp(const char *str1, const char *str2, size_t len)
// {
// 	// while neither string reached the end of it and length not reached
// 	while (*str1 != '\0' && *str2 != '\0' && len-- > 0) {
// 		// if current characters don't match
// 		if (*str1 != *str2)
// 			break;
// 			// return *str1 - *str2;

// 		str1++;
// 		str2++;
// 	}


// 	return *(const unsigned char *)str1 - *(const unsigned char *)str2;
// }

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	// loop through the string
	while (*str != '\0') {
		// if the character matches, return pointer to it
		if (*str == c)
			return (char *)str;

		// move to next character
		str++;
	}

	// check for null character at the end
	if (*str == c)
		return (char *)str;

	// if not found
	return NULL;
}

char *strrchr(const char *str, int c)
{
	// pointer to the last occurrence of the character
	char *last = NULL;

	// iterate through the string
	while(*str != '\0') {
		// if the character matches, update the pointer
		if (*str == (char)c)
			last = (char *)str;

		// move to next character
		str++;
	}

	// check for null character at the end, as c might be '\0'
	if (*str == (char)c)
		last = (char *)str;

	return last;
}

char *strstr(const char *haystack, const char *needle)
{
	// if the needle is empty, return haystack
	if (!*needle)
		return (char *)haystack;
	
	const char *p1;
	const char *p2;
	const char *start = haystack;

	// loop through the haystack
	while (*start) {
		p1 = start;
		p2 = needle;

		while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2) {
			p1++;
			p2++;
		}
		
		// if reached the end of the needle, than the entire needle was found
		if (!*p2)
			return (char *)start;

		++start;
	}

	// needle not found in haystack
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	// if the needle is empty, return haystack
	if (!*needle)
		return (char *)haystack;

	// len of haystack and needle
	size_t len_haystack = strlen(haystack);
	size_t len_needle = strlen(needle);

	// if needle longer than haystack, it cannot exist
	if (len_needle > len_haystack)
		return NULL;

	// start at the end of haystack
	for (const char *p = haystack + len_haystack - len_needle; p >= haystack; --p) {
		if (strncmp(p, needle, len_needle) == 0)
			return (char *)p;
	}

	// needle not found in the haystack
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	// cast
	char *dest = (char *)destination;
	const char *src = (const char *)source;

	// copy each byte from source to destination
	while (num--) {
		*dest++ = *src++;
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	// cast
	char *dest = (char *)destination;
	const char *src = (const char *)source;

	// create a temporary buffer (potentially overlapping regions)
	char tmp[num];
	for (size_t i = 0; i < num; i++) {
		tmp[i] = src[i];
	}

	// copy from tmp buffer to the dest
	for (size_t i = 0; i < num; ++i) {
		dest[i] = tmp[i];
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p1 = (const unsigned char *)ptr1;
	const unsigned char *p2 = (const unsigned char *)ptr2;

	while (num--) {
		if (*p1 != *p2)
			// return difference between the two in bytes
			return *p1 - *p2;
		p1++;
		p2++;
	}

	// if reached here, the two are equal
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	// cast source pointer to a char pointer
	unsigned char *p = (unsigned char *)source;

	// set each byte of the src to the value
	while (num--) {
		*p++ = (unsigned char)value;
	}

	return source;
}
