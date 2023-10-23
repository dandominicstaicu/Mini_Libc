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
	void *block = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
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
	if (nmemb == 0 || size == 0) {
		return NULL;
	}

	size_t alloc_size = nmemb * size;

	if (size != alloc_size / nmemb) {
		/* Overflow */
		return NULL;
	}

	void *block = malloc(alloc_size);
	if (!block) {
		return NULL; /* malloc failed */
	}

	memset(block, 0, alloc_size);

	return block;


	return NULL;
}

void free(void *ptr)
{
	if (!ptr) {
		return;
	}

    /* Get the metadata associated with this block. */
	struct mem_list *metadata = (struct mem_list *)(ptr - sizeof(struct mem_list));

    /* Check if it's a valid block by seeing if it exists in the mem_list. */
	struct mem_list *item = mem_list_find(metadata->start);
	if (!item) {
		/* This block wasn't allocated by malloc or has already been freed. */
		return;
	}

	if (mem_list_del(metadata->start) != 0) {
        /* Something went wrong when trying to remove from list */
		return;
	}

	/* free the block */
	munmap(metadata->start, metadata->len);
}

void *realloc(void *ptr, size_t size)
{
	/* if ptr is NULL, call the equivalent of malloc(size) */
	if (!ptr) {
		return malloc(size);
	}

	/* if size is 0, call the equivalent of free(ptr) and return NULL */
	if (size == 0) {
		free(ptr);
		return NULL;
	}

	/* Get the metadata associated with this block. */
	struct mem_list *metadata = (struct mem_list *)(ptr - sizeof(struct mem_list));
	size_t old_size = metadata->len - sizeof(struct mem_list);

	/* if the new size is the old size, just return the same ptr */
	if (old_size == size)
		return ptr;

	void *new_block = malloc(size);
	if (!new_block) {
		return NULL;
	}

	size_t copy_size = old_size < size ? old_size : size;
	memcpy(new_block, ptr, copy_size);

	/* free the old block */
	free(ptr);

	/* return the new block */
	return new_block;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb && size && __SIZE_MAX__ / nmemb < size) {
		return NULL;
	}

	size_t new_size = nmemb * size;

	return realloc(ptr, new_size);
}
