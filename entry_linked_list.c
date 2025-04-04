#include <stdlib.h>
#include <string.h>

#include "entry.h"
#include "entry_linked_list.h"

void add_entry(const char* name, struct entry** last_entry)
{
    struct entry *new_entry = malloc(sizeof(struct entry));

    strcpy(new_entry->name, name);
    new_entry->next_entry = NULL;

    if (*last_entry == NULL){
        *last_entry = new_entry;
    }
    else {
        (*last_entry)->next_entry = new_entry;
    }
}
