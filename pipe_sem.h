#ifndef pipe_sem_h
#define pipe_sem_h

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int ** pipe_array;
  int current_pipe;
  int max_pipe;
} pipe_sem_t;

// Given functions
void lock_release(int fd[2]);
void lock_acquire(int fd[2]);
void lock_init(int fd[2]);

// Pipe Semaphore functions
void pipe_sem_init(pipe_sem_t *sem, int value);
void pipe_sem_wait(pipe_sem_t *sem);
void pipe_sem_signal(pipe_sem_t *sem);

#endif