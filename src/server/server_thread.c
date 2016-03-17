#include "server_thread.h"
#include <stdio.h>

#include <netinet/in.h>
#include <netdb.h>

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <time.h>

// Variable obtenue de ../conf/conf.c
// extern const unsigned int num_server_threads;
extern const int port_number;

extern const unsigned int num_resources;
extern const unsigned int num_server_threads;
extern const unsigned int max_wait_time;
extern const unsigned int server_backlog_size;
extern const unsigned int *available_resources;


unsigned int server_socket_fd;
unsigned int request_processed;
unsigned int total_num_requests;

// Structures de données pour l'algorithme du banquier.
int *available;
int **max;
int **allocation;
int **need;

// Variable du journal.
int count_accepted = 0; // Nombre de requête acceptée (ACK reçus en réponse à REQ)
int count_on_wait = 0; // Nombre de requête en attente (WAIT reçus en réponse à REQ)
int count_invalid = 0; // Nombre de requête refusée (REFUSE reçus en réponse à REQ)
int count_dispatched = 0; // Nombre de client qui se sont terminés correctement
                          // (ACC reçu en réponse à END)

void
st_init (server_thread * st)
{
  // TODO

  // END TODO
}

void
st_process_request (server_thread * st, int socket_fd)
{

  // TODO: Remplacer le contenu de cette fonction

  char buffer[20];
  bzero (buffer, 20);
  int n = read (socket_fd, buffer, 19);
  if (n < 0)
    perror ("ERROR reading from socket");

  printf ("Thread %d received the request: %s\n", st->id, buffer);

  int answer_to_client = -(rand () % 2);
  n = sprintf (buffer, "%d", answer_to_client);
  n = write (socket_fd, buffer, n);
  if (n < 0)
    perror ("ERROR writing to socket");

  if (read (socket_fd, buffer, 255) == 0)
    {
      request_processed++;
    }
  // TODO end
};


void
st_signal ()
{
  // TODO: Remplacer le contenu de cette fonction

  sleep (2);

  // TODO end
}

void *
st_code (void *param)
{
  server_thread *st = (server_thread *) param;

  struct sockaddr_in thread_addr;
  socklen_t socket_len = sizeof (thread_addr);
  int thread_socket_fd = -1;
  int start = time (NULL);

  while (thread_socket_fd < 0)
    {
      thread_socket_fd =
	accept (server_socket_fd, (struct sockaddr *) &thread_addr,
		&socket_len);
      if ((time (NULL) - start) >= max_wait_time
	  || request_processed == total_num_requests)
	{
	  break;
	}
    }

  while (request_processed < total_num_requests)
    {
      if ((time (NULL) - start) >= max_wait_time)
	{
	  fprintf (stderr, "Time out on thread %d.\n", st->id);
	  pthread_exit (NULL);
	}
      if (thread_socket_fd > 0)
	{
	  st_process_request (st, thread_socket_fd);
	  close (thread_socket_fd);
	}
      thread_socket_fd =
	accept (server_socket_fd, (struct sockaddr *) &thread_addr,
		&socket_len);
    }
}

void
st_open_socket ()
{
  server_socket_fd = socket (AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (server_socket_fd < 0)
    perror ("ERROR opening socket");

  struct sockaddr_in serv_addr;
  bzero ((char *) &serv_addr, sizeof (serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons (port_number);

  if (bind
      (server_socket_fd, (struct sockaddr *) &serv_addr,
       sizeof (serv_addr)) < 0)
    perror ("ERROR on binding");

  listen (server_socket_fd, server_backlog_size);
}

//
// Affiche les données recueillies lors de l'exécution du
// serveur.
// La branche else ne doit PAS être modifiée.
//
void
st_print_results (FILE * fd, bool verbose)
{
  if (fd == NULL)
    fd = stdout;
  if (verbose)
    {
      fprintf (fd, "\n---- Résultat du serveur ----\n");
      fprintf (fd, "Requêtes acceptées: %d\n", count_accepted);
      fprintf (fd, "Requêtes : %d\n", count_on_wait);
      fprintf (fd, "Requêtes invalides: %d\n", count_invalid);
      fprintf (fd, "Clients : %d\n", count_dispatched);
      fprintf (fd, "Requêtes traitées: %d\n", request_processed);
    }
  else
    {
      fprintf (fd, "%d %d %d %d %d\n", count_accepted, count_on_wait,
	       count_invalid, count_dispatched, request_processed);
    }
}
