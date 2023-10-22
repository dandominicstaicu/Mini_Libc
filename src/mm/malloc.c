// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	if (size == 0) {
		return NULL;
	}

	size_t alloc_size = size + sizeof(struct mem_list);
	void *block = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
	if (block == MAP_FAILED) {
		return NULL;
	}

	struct mem_list *metadata = (struct mem_list *)block;
	metadata->start = block;
	metadata->len = alloc_size;

	if (mem_list_add(block, alloc_size) != 0) {
		munmap(block, alloc_size);
		return NULL;
	}

	return block + sizeof(struct mem_list);
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	return NULL;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return NULL;
}
