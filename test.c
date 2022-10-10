#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result = -1 % 17;
    printf("%d\n", result);
}

//comment below is from previous ioopm_hash_table_has_value
  /*
  //loop för att iterera över alla buckets
  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *entry = ht->buckets[i]; //entry = dummy
    //räkna varje entry i bucketen dvs inkrementera räknaren (exkludera dummy).
    while(entry->next != NULL) 
    {
      if(entry->next->value != NULL) //testar för NULL-värden så att det inte blir fel med strcmp
      {
        int equal = strcmp(entry->next->value, value); //blir 0 om equal. får inte ta emot NULL-värden
        if (equal == 0)
        {
          return true;
        }
      }
    entry = entry->next;
    }
  }
  return false;*/