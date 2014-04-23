/*
  Readers-writers problem
  Author: Bradley Wells
  Helped a lot by wikipedia
*/

#include "pipe_sem.c"
#include <pthread.h>

int readcount, writecount;
int readID, writeID = 0;
int time_lapse;
pipe_sem_t mutex_1, mutex_2, mutex_3, write_mutex, read_mutex;
 
void reader(){
  pipe_sem_wait(&mutex_3);
  pipe_sem_wait(&read_mutex);
  pipe_sem_wait(&mutex_1);
  readcount++;
  if(readcount == 1){
    pipe_sem_wait(&write_mutex);
  }
  pipe_sem_signal(&mutex_1);
  pipe_sem_signal(&read_mutex);
  pipe_sem_signal(&mutex_3);
 
  printf("Reader thread %d enters CS\n", readID);
  sleep(1000);
  printf("Reader thread %d exits CS\n", readID);
 
  pipe_sem_wait(&mutex_1);
  readcount--;
  if(readcount == 0){
    pipe_sem_signal(&write_mutex);
  }
  pipe_sem_signal(&mutex_1);
}
 
void writer(){
  pipe_sem_wait(&mutex_2);
  writecount++;
  if(writecount == 1){
    pipe_sem_wait(&read_mutex);
  }
  pipe_sem_signal(&mutex_2);
 
  pipe_sem_wait(&write_mutex);
  printf("Writer thread %d enters CS\n", writeID);
  sleep(1000);
  printf("Writer thread %d enters CS\n", writeID);
  pipe_sem_signal(&write_mutex);
 
  pipe_sem_wait(&mutex_2);
  writecount--;
  if(writecount == 0){
    pipe_sem_signal(&read_mutex);
  }
  pipe_sem_signal(&mutex_2);
}

int main(int argc, char* args[]){
  pipe_sem_init(&mutex_1, 1);
  pipe_sem_init(&mutex_2, 1);
  pipe_sem_init(&mutex_3, 1);
  pipe_sem_init(&write_mutex, 1);
  pipe_sem_init(&read_mutex, 1);

  readcount = 0;
  writecount = 0;

  if(argc < 2){
    fprintf(stderr, "Not enough args");
    exit(-1);
  }

  int totalcount = atoi(args[1]);
  pthread_t th[totalcount];

  int time_lapse = atoi(args[argc-1]);

  int i;
  for(i=0; i<totalcount; i++){
    if(atoi(args[i+2]) == 0){
      pthread_create(&th[i], NULL, reader, NULL);
      readID++;
    }
    else if(atoi(args[i+2]) == 1){
      pthread_create(&th[i], NULL, writer, NULL);
      writeID++;
    }
    else{
      fprintf(stderr, "Incorrect arg %s", args[i]);
      exit(-1);
    }
  }

}