#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define Success(v)      (option_t) { .success = true, .value = v };
#define Failure()       (option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)
#define No_Buckets 17

//ska vi ha dom här eller i h-filen?
typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[No_Buckets]; //vad är det här? en array av arrays?
};

//funktionssignaturer
ioopm_hash_table_t *ioopm_hash_table_create(void);
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, bool *successful);
static entry_t *find_previous_entry_for_key(entry_t *bucket, int key);
static entry_t *entry_create(int key, char *value, entry_t *next);
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, bool *successful);
static void create_dummies(ioopm_hash_table_t *ht);
static void entry_destroy(entry_t *entry);
int ioopm_hash_table_size(ioopm_hash_table_t *ht);
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);


static void create_dummies(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; ++i)
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

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key=key, entry->value=value, entry->next=next;
  return entry;
}

static void entry_destroy(entry_t *entry)
{
  free(entry);
  entry = NULL;  //free pointer
}

/*1. Iterate over the buckets in the buckets array
   1.1 For each bucket, iterate over its entries and deallocate them.
2. Deallocate the hash table data structure using free().*/
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
  for(int i = 0; i < No_Buckets; i++) //itererar över buckets array, tar bort alla entries förutom sista
  {
    entry_t *entry = ht->buckets[i]; 
    while(entry->next != NULL) //itererar över entries i bucket
    {
      entry_t *entry_temp = entry; 
      entry = entry->next;
      entry_destroy(entry_temp);
    }
    entry_destroy(entry); //förstör sista entry
  }
  free(ht);
  ht = NULL; //free pointer
}

char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, bool *successful)
{
  entry_t *tmp = find_previous_entry_for_key(ht->buckets[abs(key % No_Buckets)], key); //ändrat så att negativa keys ändrar tecken till positiva. -1 blir 1. 
  entry_t *next = tmp->next;

  if (next) //tidigare: if (next && next->value) 
  {
    if(next->key == key)
    {
      *successful = true;
      return next->value;      //Ful kod. 
    }
    else
    {    
      *successful = false;
      return NULL; 
    }
  }
  else
  {
    *successful = false;
    return NULL; 
  }
}

//vi antar att bucketen (entries) är sorterad efter key-storlek
static entry_t *find_previous_entry_for_key(entry_t *first_entry, int key)
{
  if(first_entry->next == NULL)
  {
    return first_entry;
  }
  else //gå igenom entries tills vi hittar att någon key1 är större eller lika med vår key. vi kollar next
  {
    entry_t *entry = first_entry;
    while(entry->next->key < key)  //vad händer om next är NULL? Segfault. För någonting som ligger sist. lookup 34. 
    {
      entry = entry->next;
      if (entry->next == NULL) //sista entry
      {
        return entry;
      }
    }
    return entry;  
  }
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = abs(key % No_Buckets);
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

char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, bool *successful)
{
  //använd lookup för att kolla om entry existerar i key. 
  bool successful_lookup; //gav inte det här segfault?
  ioopm_hash_table_lookup(ht, key, &successful_lookup);
  if(successful_lookup)
  {
    entry_t *first_entry = ht->buckets[abs(key % No_Buckets)]; //så vi måste inte säga att det är en int?
    entry_t *previous_entry = find_previous_entry_for_key(first_entry, key); //tar emot första entryt i bucketen
    entry_t *entry = previous_entry->next;
    char *value = entry->value;
    previous_entry->next = entry->next;
    entry_destroy(entry);
    *successful = true;
    return value;
  }
  else
  {
    *successful = false;
    return NULL; 
  }
}

//Räknar med dummy och alla element utom det sista. 
int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  int counter = 0;
  //loop för att iterera över alla buckets
  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *entry = ht->buckets[i]; //entry = dummy
    //räkna varje entry i bucketen dvs inkrementera räknaren (exkludera dummy).
    while(entry->next != NULL) 
    {
      counter++;
      entry = entry->next;
    }
  }
  return counter;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *dummy = ht->buckets[i];
    if(dummy->next != NULL)
    {
      return false;
    } 
  }
  return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *dummy = ht->buckets[i]; 
    if (dummy->next != NULL )
    {
      entry_t *entry = dummy->next;
      while(entry->next != NULL)
      {
        entry_t *entry_temp = entry; 
        entry = entry->next;
        entry_destroy(entry_temp);
      }
      entry_destroy(entry);
    }
  }
}