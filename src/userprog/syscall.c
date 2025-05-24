#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "userprog/process.h"

typedef int pid_t;

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
sys_halt (void)
{
  shutdown_power_off();
}

static void
sys_exit (int status)
{
  thread_current()->process->exit_code = status;
  thread_exit();
}

static pid_t
sys_exec (const char* cmd_line)
{
  return process_execute(cmd_line);
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  int syscall_number = *(int*)f->esp;
  switch(syscall_number){
    case SYS_HALT:
      sys_halt();
      NOT_REACHED();
      break;
    case SYS_EXIT:
      sys_exit(*(int*)(f->esp + 4));
      NOT_REACHED();
      break;
    case SYS_EXEC:
      f->eax = sys_exec((const char*)*(int*)(f->esp + 4));
      break;
    default:
      printf("[ERROR] system call %d is unimplemented!\n", syscall_number);
      sys_exit(-1);
      break;
  }
}
