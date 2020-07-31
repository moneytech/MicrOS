#include "../../signal.h"

void default_sigsegv_handler(int param)
{
    fprintf(stderr, "SIGSEGV received. Address: %#x\n", param);
    micros_process_exit(-1, false);
}