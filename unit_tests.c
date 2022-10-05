#include <CUnit/Basic.h>
#include "hash_table.h"

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void ioopm_hash_table_lookup_test() //(ioopm_hash_table_t *ht, int key) 
{
  // TODO: Stub
  //return NULL; TODO: SKA RETURNERA NULL! 
}

void test_create_destroy()        
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once(ioopm_hash_table_t *ht)
{
  int key = 0;
  char *value = " ";             //changed the value to "" from NULL
  bool successful;
  //CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key, &successful));
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_lookup(ht,key, &successful);
  CU_ASSERT_TRUE(successful);     //kollar att lookup är successful innan vi tittar om värdena är samma. 
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht,key, &successful), value); //FIXME returnerar NULL om lookup är false och testet blir då true
}

void test_insert_twice(ioopm_hash_table_t *ht)          
{
  int key = 1;
  char *value1 = " ";          //changed the value to "" from NULL     
  bool successful;
  //CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key, &successful));
  ioopm_hash_table_insert(ht, key, value1);

  //kollar att lookupen är successful dvs. att den hittar ett värde under key
  ioopm_hash_table_lookup(ht,key, &successful);
  CU_ASSERT_TRUE(successful);

  //kollar att värdet vi la in är samma som värdet som ligger under key 
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht,key, &successful), value1);

  //vi lägger in ett andra värde och kollar att insert funkar
  char *value2 = " ";
  ioopm_hash_table_insert(ht, key, value2);
  ioopm_hash_table_lookup(ht,key, &successful);
  CU_ASSERT_TRUE(successful);
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht,key,&successful), value2); 
}

//testar om ht är tomt. 
//vi har lagt in dummies,
void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   bool successful;
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical
     {
      CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i, &successful));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1, &successful)); //ändrat från -1 till 1. 
   ioopm_hash_table_destroy(ht);
}

void test_remove_inserted_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 5;
  char *value = "hej";
  bool successful;
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_remove(ht, key, &successful);
  CU_ASSERT_TRUE(successful);
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key, &successful));
  ioopm_hash_table_destroy(ht);
}

void test_remove_not_inserted_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 5;
  bool successful;
  ioopm_hash_table_remove(ht, key, &successful);
  CU_ASSERT_FALSE(successful);
  ioopm_hash_table_destroy(ht);
}

void test_remove_last_and_second_last_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  bool successful;
  char *value = " ";
  ioopm_hash_table_insert(ht, (int) 17, value); //NULL-värden på values gav inte ett segfault. 
  ioopm_hash_table_insert(ht, (int) 34, value);

  ioopm_hash_table_remove(ht, 17, &successful);
  CU_ASSERT_TRUE(successful);
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, 17, &successful));
  CU_ASSERT_FALSE(successful);

  ioopm_hash_table_remove(ht, 34, &successful);
  CU_ASSERT_TRUE(successful);
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, 34, &successful));
  CU_ASSERT_FALSE(successful);

  ioopm_hash_table_destroy(ht);
}

void test_empty_ht_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int size = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL((int)0,size);
  ioopm_hash_table_destroy(ht);
}

void test_one_entry_ht_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *value = " ";
  ioopm_hash_table_insert(ht, (int) 1, value);
  int size = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL((int)1,size);
  ioopm_hash_table_destroy(ht);
}

void test_several_entries_ht_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *value = " ";
  ioopm_hash_table_insert(ht, (int) 1, value);
  ioopm_hash_table_insert(ht, (int) 18, value);
  ioopm_hash_table_insert(ht, (int) 7, value);
  int size = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL((int)3,size);
  ioopm_hash_table_destroy(ht);  
}

void test_ht_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_insert(ht, (int) 2, NULL);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_ht_clear()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, (int) 2, NULL);
  ioopm_hash_table_insert(ht, (int) 19, NULL);
  ioopm_hash_table_insert(ht, (int) 0, NULL);
  ioopm_hash_table_clear(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void ioopm_hash_table_insert_test() //(ioopm_hash_table_t *ht, int key, char *value) 
{
  //testar 1;2;3
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  test_insert_once(ht);
  test_insert_twice(ht);
  //test_insert_invalid(ht);
  ioopm_hash_table_destroy(ht);

  //testar 1;1
  ht = ioopm_hash_table_create();
  test_insert_once(ht);
  test_insert_once(ht);
  ioopm_hash_table_destroy(ht);

  //testar 2;2 
  ht = ioopm_hash_table_create();
  test_insert_twice(ht);
  test_insert_twice(ht);
  ioopm_hash_table_destroy(ht);

  //testar 3;3
  ht = ioopm_hash_table_create();
  //test_insert_invalid(ht);
  //test_insert_invalid(ht);
  ioopm_hash_table_destroy(ht);

  //testar 1;2
  ht = ioopm_hash_table_create();
  test_insert_once(ht);
  test_insert_twice(ht);
  ioopm_hash_table_destroy(ht);

  //testar 1;3
  ht = ioopm_hash_table_create();
  test_insert_once(ht);
  //test_insert_invalid(ht);
  ioopm_hash_table_destroy(ht);

  //testar 2;3
  ht = ioopm_hash_table_create();
  test_insert_twice(ht);
 //test_insert_invalid(ht);
  ioopm_hash_table_destroy(ht);
  ht = NULL;               //avrefererar pointer till NULL, dangling pointer annars. 
}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();
// We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }
  CU_pSuite test_suite_insert = CU_add_suite("Testing insert", init_suite, clean_suite);
  if (test_suite_insert == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }
  CU_pSuite test_suite_size = CU_add_suite("Testing size", init_suite, clean_suite);
  if (test_suite_insert == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "Lookup hash table", ioopm_hash_table_lookup_test) == NULL) ||
    //(CU_add_test(my_test_suite, "Insert hash table", ioopm_hash_table_insert_test) == NULL) ||
    //(CU_add_test(test_suite_insert, "Insert hash table once", test_insert_once) == NULL) ||
    //(CU_add_test(test_suite_insert, "Insert hash table twice", test_insert_twice) == NULL) ||
    //(CU_add_test(test_suite_insert, "Insert hash table invalid", test_insert_invalid) == NULL) ||
    (CU_add_test(test_suite_insert, "Lookup empty hash table", test_lookup_empty) == NULL) ||
    (CU_add_test(test_suite_insert, "Insert hash table ALL", ioopm_hash_table_insert_test) == NULL) ||
    (CU_add_test(test_suite_insert, "Remove inserted entry in hash table", test_remove_inserted_entry) == NULL) ||
    (CU_add_test(test_suite_insert, "Remove not inserted entry in hash table", test_remove_not_inserted_entry) == NULL) ||
    (CU_add_test(test_suite_insert, "Remove last and next to last entry", test_remove_last_and_second_last_entry) == NULL) ||
    (CU_add_test(test_suite_size, "Size of empty hash table", test_empty_ht_size) == NULL) ||
    (CU_add_test(test_suite_size, "Size of hash table with one entry", test_one_entry_ht_size) == NULL) ||
    (CU_add_test(test_suite_size, "Size of hash table with several entries", test_several_entries_ht_size) == NULL) ||
    (CU_add_test(test_suite_size, "Check if hash table is empty after insertion and without", test_ht_empty) == NULL) ||
    (CU_add_test(test_suite_size, "Clear hash table", test_ht_clear) == NULL) ||
    (CU_add_test(my_test_suite, "Destroy hash table", test_create_destroy) == NULL) || 

  
    0
    )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}

