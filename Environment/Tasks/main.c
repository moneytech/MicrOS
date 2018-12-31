#include <micros.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    uint32_t last_update_time = micros_timer_get_system_clock();
    micros_process_set_current_process_name("TASKS");

    while (1)
    {
        micros_console_clear();
        micros_console_print_string("TASKS v1.0 @ MicrOS\n");
        micros_console_print_string("_______________________________________________\n");
        micros_console_print_string("\n");

        uint32_t processes_count = micros_process_get_processes_count();
        micros_process_user_info *processes = malloc(sizeof(micros_process_user_info) * processes_count);

        micros_process_get_all_processes_info(processes);
        uint32_t total_cpu_usage = 0;

        for (int i = 0; i < processes_count; i++)
        {
            micros_process_user_info *process = &processes[i];
            total_cpu_usage += process->cpu_usage;
        }

        for (int i = 0; i < processes_count; i++)
        {
            char buffer[32];
            micros_process_user_info *process = &processes[i];
            micros_console_print_string(process->name);
            micros_console_print_string(" - ");
            micros_console_print_string("ID: ");

            itoa(process->id, buffer, 10);
            micros_console_print_string(buffer);
            micros_console_print_string(", CPU: ");

            itoa((process->cpu_usage * 100) / total_cpu_usage, buffer, 10);
            micros_console_print_string(buffer);
            micros_console_print_string(" %, MEMORY: ");

            itoa(process->memory_usage, buffer, 10);
            micros_console_print_string(buffer);
            micros_console_print_string(" MB");
            micros_console_print_string("\n");
        }

        free(processes);

        while (last_update_time + 1000 >= micros_timer_get_system_clock())
            ;
        last_update_time = micros_timer_get_system_clock();
    }
    return 0;
}