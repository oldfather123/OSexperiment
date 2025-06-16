#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include <list.h>
#include "threads/thread.h"
#include "threads/synch.h"
#include "filesys/file.h"
#include "filesys/filesys.h"

typedef int pid_t;

enum process_status
{
    PROCESS_LOADING, /* Default state. */
    PROCESS_FAILED,  /* Failed to load. */
    PROCESS_NORMAL,  /* Running process. */
    PROCESS_EXITED,  /* Exited normally. */
};

struct process_control_block
{
    struct thread *thread;
    pid_t pid;
    enum process_status status;
    int exit_code;
    struct list_elem allelem;   /* List element for all processes list. */
    struct list_elem elem;      /* List element for children list. */
    struct list children;       /* List of children. */
    struct process *parent;     /* Parent. */
    struct semaphore sema_load; /* Parent block on this while loading. */
    struct semaphore sema_wait; /* Parent block on this while waiting. */
    struct list files;          /* Opening files. */
    int fd;                     /* Max file descriptor num. */
    struct file *file;          /* Executable file loaded by self. */
};

void process_init(void);
tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);
struct process *process_create(struct thread *t);
struct process *get_process(pid_t pid);
struct process *get_child(pid_t pid);

#endif /**< userprog/process.h */
