#include <stdlib.h>

#include "client_thread.h"

extern unsigned int num_clients;

int
main (int argc, char *argv[argc + 1])
{
  client_thread client_threads[num_clients];

  for (unsigned int i = 0; i < num_clients; i++)
    {
      ct_init (&(client_threads[i]));
    }

  for (unsigned int i = 0; i < num_clients; i++)
    {
      ct_create_and_start (&(client_threads[i]));
    }

  ct_wait_server ();

  // Affiche le journal.
  st_print_results (stdout, true);
  FILE *fp=fopen("client_log", "w");
  if (fp == NULL)
    {
      fprintf(stderr, "Could not print log");
      return EXIT_FAILURE;
    }
  st_print_results (fp, false);
  fclose(fp);

  return EXIT_SUCCESS;
}
