// malloc.c
#include "minicrt.h"

typedef struct _heap_header
{
	enum {
		HEAP_BLOCK_FREE = 0xABABABABAB, // magic number of bree block
		HEAP_BLOCK_USED = 0xCDCDCDCDCD, // magic number of used block
	} type; // block type FREE/USED
	
	unsigned size; // block size including header
	struct _heap_header* next;
	struct _heap_header* prev;
} heap_header;

#define ADDR_ADD(a,o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header* list_head = NULL;

void free(void* ptr)
{
	heap_header* header = (heap_header*)ADDR_ADD(ptr, -HEADER_SIZE);
	if(header->type != HEAP_BLOCK_USED)
		return;
	
	header->type = HEAP_BLOCK_FREE;
	if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE) {
		// merge
		header->prev->next = header->next;
		if(header->next != NULL)
			header->next->prev = header->prev;
		header->prev->size += header->size;
		
		header = header->prev;
	}
	
	if(header->next != NULL && header->next->type == HEAP_BLOCK_FREE) {
		// merge
		header->size += header->next->size;
		header->next = header->next->next;
	}
}

void* malloc(unsigned size)
{
	heap_header *header;
	
	if(size == 0)
		return NULL;
		
	header = list_head;
	while(header != 0) {
		if(header->type == HEAP_BLOCK_USED) {
			header = header->next;
			continue;
		}
		
		if(header->size > size + HEADER_SIZE && header->size <= size + HEADER_SIZE * 2) {
			header->size = HEAP_BLOCK_USED;
		}
		
		if(header->size > size + HEADER_SIZE *2) {
			// split
			heap_header* next = (heap_header*)ADDR_ADD(header.size + HEADER_SIZE);
			next->prev = header;
			next->next = header->next;
			next->type = HEAP_BLOCK_FREE;
			next->size = header->size - (size - HEADER_SIZE);
			header
		}
	}
}