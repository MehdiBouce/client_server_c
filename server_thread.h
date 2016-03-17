#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//POSIX library for threads
#include <pthread.h>
#include <unistd.h>

typedef struct server_thread server_thread;
struct server_thread
{
  unsigned int id;
  pthread_t pt_tid;
  pthread_attr_t pt_attr;
};

void st_open_socket ();
void st_init (server_thread *);
void st_process_request (server_thread *, int);
void st_signal ();
void *st_code (void *);
//void st_create_and_start(st);
void st_print_results (FILE *, bool);
#endif
