
#include "pipe_sem.h"

/*
 * Library Functions
 */
void pipe_sem_init(pipe_sem_t *sem, int value)
{
  sem->pipe_array = (int**) malloc(sizeof(int) * 2 * value);
  if(!(sem->pipe_array)){
    fprintf(stderr, "Malloc Failure\n");
    exit(-1);
  }
  sem->current_pipe = value-1;
  sem->max_pipe = value-1;
  int i;
  for(i=0; i<value; i++){
    lock_init(sem->pipe_array[i]);
  }
}

void pipe_sem_wait(pipe_sem_t *sem)
{
  if(sem->current_pipe == -1){
    lock_acquire(sem->pipe_array[0]);
  }
  else{
    lock_acquire(sem->pipe_array[sem->current_pipe]);
    sem->current_pipe--;
  }
  
}

void pipe_sem_signal(pipe_sem_t *sem)
{
  sem->current_pipe++;
  if(sem->current_pipe > sem->max_pipe){
    fprintf(stderr, "Current pipe is more than max pipe");
    exit(-1);
  }
  lock_release(sem->pipe_array[sem->current_pipe]);
}

/*
 * Helper Functions
 */
void lock_release(int fd[2])
{
  write(fd[1], "ok", sizeof("ok"));
  exit(0);
}

void lock_acquire(int fd[2])
{
  char buf[10];
  read(fd[0], buf, 10);
}

void lock_init(int fd[2])
{
  if(pipe(fd) != 0) {
    perror("fail to initialize pipe\n");
    exit(1);
  }
  lock_release(fd);
}
