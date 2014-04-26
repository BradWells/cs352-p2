all:
	gcc rw_test.c linked_pipes.c pipe_sem.c -lpthread -o test

clean:
	rm -rf *o test