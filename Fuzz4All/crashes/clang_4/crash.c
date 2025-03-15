#include <stdlib.h>
<fim_suffix>= malloc(sizeof(*ptr));
   *ptr = &new_cell;
   new_cell.val = val;
   new_cell.next = ht->cells;
   ht->cells = new_cell.next;
}

 

void add_new_value(Hashtable *ht, char *key, int row, int col, int val) {
   List *ptr;
   ptr = calloc(1, sizeof(List));
   ptr->row = row;
   ptr->col = col;
   ptr->val = val;
   ptr->next = ht->cells;
   ht->cells = ptr;
}


 

void add_new_value(Hashtable *ht, char *key, int row, int col, int val) {
   List *ptr;
   ptr = malloc(sizeof(*ptr));
   *ptr = (List) {.row = row,.col = col,.val = val,.next = ht->cells };
   ht->cells = ptr;
}

 

void add_new_value(Hashtable *ht, char *key, int row, int col, int val) {
   List *ptr;
   ptr = malloc(sizeof(*ptr));
   ptr->row = malloc(sizeof(int));
   ptr->col = malloc(sizeof(int));
   ptr->val = malloc(sizeof(int));
   ptr->next = malloc(sizeof(ptr));

   *ptr->row = row;
   *ptr->col = col;
   *ptr->val = val;
   *ptr->next = ht->cells;
   ht->cells = ptr;
}
 

void add_new_value(Hashtable *ht, char *key, int row, int col, int val) {
   List **ptr;
   ptr = malloc(sizeof(*ptr));
   *ptr = malloc(sizeof(List));
   **ptr = (List) {.row = row,.col = col,.val = val,.next = ht->cells };
   ht->cells = *ptr;
}
 
<fim_middle>#include <stdio.h>
#include <string.h>
#define LEN 50
#define LEN2 50
int main()
{
   char * s, *p;
   char s1
