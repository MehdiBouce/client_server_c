#include <stdio.h>

#include "client_thread.h"

// Variable de configuration.
extern const int port_number;
extern const unsigned int num_clients;
extern const unsigned int num_resources;
extern const unsigned int num_request_per_client;
extern const unsigned int **max_resources_per_client;

// Variable du journal.
unsigned int count = 0; // Nombre de requêtes (REQ envoyés)
int count_accepted = 0; // Nombre de requête acceptée (ACK reçus en réponse à REQ)
int count_on_wait = 0; // Nombre de requête en attente (WAIT reçus en réponse à REQ)
int count_invalid = 0; // Nombre de requête refusée (REFUSE reçus en réponse à REQ)
int count_dispatched = 0; // Nombre de client qui se sont terminés correctement
                          // (ACC reçu en réponse à END)
int request_sent = 0; // Nombre total de requêtes envoyées.

void
send_request (int client_id, int request_id, int socket_fd)
{

  // TP2 TODO

  fprintf (stdout, "Client %d is sending its %d request\n", client_id,
	   request_id);

  // TP2 TODO:END

}


void *
ct_code (void *param)
{
  int socket_fd;
  client_thread *ct = (client_thread *) param;

  for (unsigned int request_id = 0; request_id < num_request_per_client;
       request_id++)
    {

      // TP2 TODO

      send_request (ct->id, request_id, socket_fd);

      // TP2 TODO:END

    }

  pthread_exit (NULL);
}


// 
// Vous devez changer le contenu de cette fonction afin de régler le
// problème de synchronisation de la terminaison.
// Le client doit attendre que le serveur termine le traitement de chacune
// de ses requêtes avant de terminer l'exécution
//
void
ct_wait_server ()
{

  // TP2 TODO

  sleep (2);

  // TP2 TODO:END

}


void
ct_init (client_thread * ct)
{
  ct->id = count++;
}

void
ct_create_and_start (client_thread * ct)
{
  pthread_attr_init (&(ct->pt_attr));
  pthread_create (&(ct->pt_tid), &(ct->pt_attr), &ct_code, ct);
  pthread_detach (ct->pt_tid);
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
      fprintf (fd, "\n---- Résultat du client ----\n");
      fprintf (fd, "Requêtes acceptées: %d\n", count_accepted);
      fprintf (fd, "Requêtes : %d\n", count_on_wait);
      fprintf (fd, "Requêtes invalides: %d\n", count_invalid);
      fprintf (fd, "Clients : %d\n", count_dispatched);
      fprintf (fd, "Requêtes envoyées: %d\n", request_sent);
    }
  else
    {
      fprintf (fd, "%d %d %d %d %d\n", count_accepted, count_on_wait,
	       count_invalid, count_dispatched, request_sent);
    }
}
