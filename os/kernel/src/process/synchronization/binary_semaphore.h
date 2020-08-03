#ifndef BINARY_SEMAPHORE_H
#define BINARY_SEMAPHORE_H

#include <kvector.h>
#include <string.h>
#include "memory/heap/heap.h"
#include "process/manager/process_manager.h"

typedef int32_t binary_semaphore;

typedef struct binary_semaphore_data
{
	char* name;
    int32_t semaphore_id;
    kvector processes;
	kvector blocked_processes;
    int32_t blocked;
} binary_semaphore_data;

void binary_semaphore_init();

binary_semaphore create_named_binary_semaphore(char* name);

void acquire(binary_semaphore semaphore);

int32_t __get_index_of_binary_semaphore_by_name(kvector *vector, char* name);

int32_t __get_index_of_binary_semaphore_by_id(kvector *vector, binary_semaphore id);

#endif