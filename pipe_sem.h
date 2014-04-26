#ifndef pipe_sem_h
#define pipe_sem_h

#include <stdio.h>
#include <stdlib.h>
#include "linked_pipes.h"

typedef struct
{
	pipe_node_t* tail_node;
  pipe_node_t* head_node;
  int count;
} pipe_sem_t;

// Given functions
void lock_release(int fd[2]);
void lock_acquire(int fd[2]);
void lock_init(int fd[2]);

// Pipe Semaphore functions
void pipe_sem_init(pipe_sem_t *sem, int value);
void pipe_sem_wait(pipe_sem_t *sem);
void pipe_sem_signal(pipe_sem_t *sem);

pipe_node_t* remove_head_node(pipe_sem_t *sem);
void free_and_release(pipe_node_t* node);

#endif