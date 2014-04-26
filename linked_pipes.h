#ifndef Linked_pipes
#define Linked_pipes

typedef struct pipe_node
{
	int pipe[2];
	struct pipe_node* prev;
	struct pipe_node* next;
} pipe_node_t;

#endif
