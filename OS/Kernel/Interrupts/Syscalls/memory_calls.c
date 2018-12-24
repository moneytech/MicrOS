#include "memory_calls.h"

void syscall_alloc_memory_call(interrupt_state *state)
{
    state->registers.eax = (uint32_t)heap_user_alloc(state->registers.ebx, state->registers.ecx);
}

void syscall_realloc_memory_call(interrupt_state *state)
{
    state->registers.eax = heap_user_realloc((void *)state->registers.ebx, state->registers.ecx, state->registers.edx);
}

void syscall_dealloc_memory_call(interrupt_state *state)
{
    heap_user_dealloc((void *)state->registers.ebx);
}