#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

typedef int pid_t;

struct process_control_block
{
    struct thread *thread;
    pid_t pid;
    int exit_code;
};

tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);

#endif /**< userprog/process.h */
