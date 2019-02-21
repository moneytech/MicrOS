#include "syscalls_manager.h"

void (*syscall_handlers[SYSCALLS_MANAGER_MAX_HANDLERS])(interrupt_state *state);

void syscalls_manager_init()
{
    idt_attach_syscalls_manager(syscalls_manager_call);

    // 0x0X - Heap
    syscalls_manager_attach_handler(0x00, syscall_heap_alloc_memory);
    syscalls_manager_attach_handler(0x01, syscall_heap_realloc_memory);
    syscalls_manager_attach_handler(0x02, syscall_heap_dealloc_memory);
    syscalls_manager_attach_handler(0x03, syscall_heap_get_object_size);
    syscalls_manager_attach_handler(0x04, syscall_heap_verify_integrity);
    syscalls_manager_attach_handler(0x05, syscall_heap_get_process_heap);

    // 0x1X - VGA
    syscalls_manager_attach_handler(0x10, syscall_vga_print_char);
    syscalls_manager_attach_handler(0x11, syscall_vga_print_string);
    syscalls_manager_attach_handler(0x12, syscall_vga_get_char_at_position);
    syscalls_manager_attach_handler(0x13, syscall_vga_set_cursor_position);
    syscalls_manager_attach_handler(0x14, syscall_vga_get_cursor_position);
    syscalls_manager_attach_handler(0x15, syscall_vga_clear);
    syscalls_manager_attach_handler(0x16, syscall_vga_set_cursor_visibility);

    // 0x2X - Keyboard
    syscalls_manager_attach_handler(0x20, syscall_keyboard_is_key_pressed);
    syscalls_manager_attach_handler(0x21, syscall_keyboard_get_pressed_key);
    syscalls_manager_attach_handler(0x22, syscall_keyboard_wait_for_key_press);

    // 0x3X - PCI

    // 0x4X - RTC
    syscalls_manager_attach_handler(0x40, syscall_rtc_get_time);

    // 0x5X - File system
    syscalls_manager_attach_handler(0x50, syscall_filesystem_get_file_info);
    syscalls_manager_attach_handler(0x51, syscall_filesystem_get_directory_info);
    syscalls_manager_attach_handler(0x52, syscall_filesystem_read_file);

    // 0x6X - Timer
    syscalls_manager_attach_handler(0x60, syscall_timer_get_system_clock);

    // 0x7X - Power

    // 0x8X - PC Speaker
    syscalls_manager_attach_handler(0x80, syscall_pc_speaker_enable_sound);
    syscalls_manager_attach_handler(0x81, syscall_pc_speaker_disable_sound);

    // 0x9X - Processes
    syscalls_manager_attach_handler(0x90, syscall_process_exit);
    syscalls_manager_attach_handler(0x91, syscall_process_get_processes_count);
    syscalls_manager_attach_handler(0x92, syscall_process_get_current_process_info);
    syscalls_manager_attach_handler(0x93, syscall_process_get_process_info);
    syscalls_manager_attach_handler(0x94, syscall_process_get_all_processes_info);
    syscalls_manager_attach_handler(0x95, syscall_process_set_current_process_name);
    syscalls_manager_attach_handler(0x96, syscall_process_current_process_sleep);

    // 0xAX - Memory
    syscalls_manager_attach_handler(0xA0, syscall_memory_get_physical_memory_stats);
}

void syscalls_manager_attach_handler(uint8_t function_number, void (*handler)(interrupt_state *state))
{
    syscall_handlers[function_number] = handler;
}

void syscalls_manager_detach_handler(uint8_t function_number)
{
    syscall_handlers[function_number] = 0;
}

void syscalls_manager_call(interrupt_state *state)
{
    if (syscall_handlers[state->registers.eax] != 0)
    {
        (*syscall_handlers[state->registers.eax])(state);
    }
}