#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>

//ska vi ha dom här 
typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17]; //vad är det här? en array av arrays?
};

//funktionssignaturer
ioopm_hash_table_t *ioopm_hash_table_create(void);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);
entry_t *find_previous_entry_for_key(entry_t *bucket, int key);
entry_t *entry_create(int key, char *value, entry_t *next);
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);

void create_dummies(ioopm_hash_table_t *ht)
{
  int ht_size = 17;
  for (int i = 0; i < ht_size; ++i)
  {
    entry_t *dummy = entry_create(0,NULL,NULL);
    ht->buckets[i] = dummy;
  }
}

ioopm_hash_table_t *ioopm_hash_table_create(void)   //type for this function is unknown 
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
  create_dummies(ht);
  return ht;
}

entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key=key, entry->value=value, entry->next=next;
  return entry;
}

void entry_destroy(entry_t *entry)
{
  free(entry);
  entry = NULL;  //free pointer
}

/*1. Iterate over the buckets in the buckets array
   1.1 For each bucket, iterate over its entries and deallocate them.
2. Deallocate the hash table data structure using free().*/
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
  int ht_size = 17; //FIXME hårdkodat bucket size 17. 
  for(int i = 0; i < ht_size; i++) //itererar över buckets array, tar bort alla entries förutom sista
  {
    entry_t *entry = ht->buckets[i]; 
    while(entry->next != NULL) //itererar över entries i bucket
    {
      entry_t *entry_temp = entry; //alias eller kopia?
      entry = entry->next;
      entry_destroy(entry_temp);
    }
    entry_destroy(entry); //förstör sista entry
  }
  free(ht);
  ht = NULL; //free pointer
}

char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) //pekarsemantik eller värdesemantik?
{
  return NULL; //TODO
}

//vi antar att bucketen (entries) är sorterad efter key-storlek
entry_t *find_previous_entry_for_key(entry_t *first_entry, int key)
{
  if(first_entry->next == NULL)
  {
    return first_entry;
  }
  else //gå igenom entries tills vi hittar att någon key1 är större eller lika med vår key. vi kollar next
  {
    entry_t *entry = first_entry;
    while(key < entry->next->key) 
    {
      entry = entry->next;
    }
    return entry;  
  }
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}

