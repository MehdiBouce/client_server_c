// Common configuration
const int port_number = 2016;

// Client configuration
#define NUM_CLIENTS 5
#define NUM_RESOURCES 3
const unsigned int num_clients = NUM_CLIENTS;
const unsigned int num_resources = NUM_RESOURCES;
const unsigned int num_request_per_client = 4;
const unsigned int max_resources_per_client[NUM_CLIENTS][NUM_RESOURCES] = {
  {7, 5, 3},
  {3, 2, 2},
  {9, 1, 2},
  {2, 2, 2},
  {4, 3, 3},
};
