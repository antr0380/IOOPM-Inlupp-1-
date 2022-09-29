#include "hash_table.h"
#include <stdlib.h>

typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17];
};

ioopm_hash_table_t *ioopm_hash_table_create(void)   //type for this function is unknown 
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
    free(ht);
}

char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) //pekarsemantik eller värdesemantik?
{
  return NULL; //TODO
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  return; //TODO 
}