
#include "pipe_sem.h"


/* My helper functions */

/*
  Removes and frees the first node in the list of pipes
*/
pipe_node_t* remove_head_node(pipe_sem_t *sem){
  if(sem->head_node == NULL){
    fprintf(stderr, "Head is null, can't remove");
    exit(1);
  }
  pipe_node_t *temp = sem->head_node;
  sem->head_node = sem->head_node->next;
  if(sem->head_node){
    sem->head_node->prev = NULL;
  }
  return temp;
}

void release_and_free(pipe_node_t* node){
  lock_release(node->pipe);
  //Freeing here might be bad
  free(node);
}


/*
 * Library Functions
 */
void pipe_sem_init(pipe_sem_t *sem, int value)
{
  sem->count= value;
  sem->head_node = NULL;
  sem->tail_node = NULL;
}

void pipe_sem_wait(pipe_sem_t *sem)
{
  //Easy semaphore implementation for testing
  // while(sem->count<=0);
  // sem->count--;

  //Actual implementation
  if(sem->count<=0){
    pipe_node_t* new_node = (pipe_node_t*) malloc(sizeof(pipe_node_t));
    if(!(new_node)){
      fprintf(stderr, "Malloc Failure\n");
      exit(1);
    }
    lock_acquire(new_node->pipe);
    if(sem->head_node == NULL){
      sem->head_node = new_node;
      sem->tail_node = new_node;
    }
    else{
      sem->tail_node->next = new_node;
      new_node->prev = sem->tail_node;
      sem->tail_node = new_node;
    }
  }
  else{
    sem->count--;
  }
}

void pipe_sem_signal(pipe_sem_t *sem)
{
  //Easy semaphore implementation for testing
  // sem->count++;

  //Actual implementation
  if(sem->head_node != NULL){
    pipe_node_t* current_node = remove_head_node(sem);
    release_and_free(current_node);
  }
  else{
    sem->count++;
  }
}

/*
 * Helper Functions
 */
void lock_release(int fd[2])
{
  write(fd[1], "ok", sizeof("ok"));
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
