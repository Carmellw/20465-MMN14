#include <stdlib.h>
#include <string.h>

#include "extern_struct.h"
#include "entry_linked_list.h"

void add_extern(const char* name, struct extern_struct** last_entry)
{
    struct extern_struct *new_extern = malloc(sizeof(struct extern_struct));

    strcpy(new_extern->name, name);
    new_extern->next_extern = NULL;

    if (*last_entry == NULL){
        *last_entry = new_extern;
    }
    else {
        (*last_entry)->next_extern = new_extern;
    }
}
