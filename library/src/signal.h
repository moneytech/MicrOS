#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>
#include "stdio.h"
#include "micros.h"

//! (Signal Abort) Abnormal termination, such as is initiated by the abort function.
#define SIGABRT 0

//! (Signal Floating-Point Exception) Erroneous arithmetic operation, such as zero divide or an operation resulting in overflow (not necessarily with a floating-point operation).
#define SIGFPE 1

//! (Signal Illegal Instruction) Invalid function image, such as an illegal instruction. This is generally due to a corruption in the code or to an attempt to execute data.
#define SIGILL 2

//! (Signal Interrupt) Interactive attention signal. Generally generated by the application user.
#define SIGINT 3

//! (Signal Segmentation Violation) Invalid access to storage: When a program tries to read or write outside the memory it has allocated.
#define SIGSEGV 4

//! (Signal Terminate) Termination request sent to program.
#define SIGTERM 5

//! Ignore Signal: The signal is ignored.
#define SIG_IGN 0

//! Default handling: The signal is handled by the default action for that particular signal.
#define SIG_DFL 1

//! Special return value indicating failure.
#define SIG_ERR 2

//! Integral type.
/*! Integral type of an object that can be accessed as an atomic entity, even in the presence of asynchronous signals. !*/
typedef int32_t sig_atomic_t;

//! Signal function signature
typedef void (*signal_func)(int);

//! Array containing all signal handlers
extern signal_func signal_handlers[6];

#ifdef __cplusplus
extern "C" {
#endif

//! Set function to handle signal.
/*!
    Specifies a way to handle the signals with the signal number specified by sig.
    \param sig The signal value to which a handling function is set.
    \param func A pointer to a function. This may either be a function defined by the programmer or one of the following predefined functions: SIG_DFL (handle) or SIG_IGN (ignore).
    \return If the request is successful, the function returns a pointer to the particular handler function which was in charge of handling this signal before the call, if any. Or either SIG_DFL or SIG_IGN if before the call the signal was being handled by the default handler or was being ignored, respectivelly. If the function was not successful in registering the new signal handling procedure, it returns SIG_ERR and errno may be set to a positive value.
*/
void (*signal(int sig, signal_func func))(int);

//! Generates a signal.
/*!
    The signal value to raise.
    \param sig The signal value to which a handling function is set.
    \return Returns zero if successful, and a value different from zero otherwise.
*/
int raise(int sig);

//! Generates a signal with the specified parameter.
/*!
    The signal value to raise.
    \param sig The signal value to which a handling function is set.
    \param param The signal parameter.
    \return Returns zero if successful, and a value different from zero otherwise.
*/
int raise_with_param(int sig, int param);

//! Default signal handle for SIGABRT.
/*!
    This handler can be set by passing SIG_DFL in sig parameter in signal function.
    \param param Signal parameter.
*/
void default_sigabrt_handler(int param);

//! Default signal handle for SIGFPE.
/*!
    This handler can be set by passing SIG_DFL in sig parameter in signal function.
    \param param Signal parameter.
*/
void default_sigfpe_handler(int param);

//! Default signal handle for SIGILL.
/*!
    This handler can be set by passing SIG_DFL in sig parameter in signal function.
    \param param Signal parameter.
*/
void default_sigill_handler(int param);

//! Default signal handle for SIGINT.
/*!
    This handler can be set by passing SIG_DFL in sig parameter in signal function.
    \param param Signal parameter.
*/
void default_sigint_handler(int param);

//! Default signal handle for SIGSEGV.
/*!
    This handler can be set by passing SIG_DFL in sig parameter in signal function.
    \param param Signal parameter.
*/
void default_sigsegv_handler(int param);

//! Default signal handle for SIGTERM.
/*!
    This handler can be set by passing SIG_DFL in sig parameter in signal function.
    \param param Signal parameter.
*/
void default_sigterm_handler(int param);

//! Initialize default signal handlers.
/*!
    Assign default signal handlers to the internal array.
*/
void __signal_init();

//! Get default handler for the specified signal.
/*!
    Gets default signal handler based on the passed signal type.
*/
signal_func __signal_get_defualt_handler(int sig);

#ifdef __cplusplus
}
#endif

#endif