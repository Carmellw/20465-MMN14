#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "macro.h"
#include "marco_linked_list.h"

char *get_macro_name(char *line) {
    char *name;
    strtok(line, " ");
    name = strtok(NULL, " ");
    if (name[strlen(name)-1] == '\n') {
        name[strlen(name)-1] = '\0';
    }
    return name;
}

int main(int argc, char** argv) {

    FILE* fp = fopen("/Users/carmellwasserman/Desktop/example1.as", "r");
    char line[MAX_LINE_LEN];
    int is_in_mcro = FALSE;
    struct macro *first_macro = NULL;
    struct macro *current_macro = NULL;
    struct line *current_line = NULL;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        if (FALSE == is_in_mcro && strncmp(line, "mcro", 4) == 0) {
            is_in_mcro = TRUE;
            add_macro(get_macro_name(line), &current_macro);
            if (first_macro == NULL) {
                first_macro = current_macro;
            }
        }
        else if (TRUE == is_in_mcro && strncmp(line, "endmcro", 7) == 0) {
            is_in_mcro = FALSE;
        }
        else if (TRUE == is_in_mcro) {
            if (current_macro->first_line == NULL) {
                add_first_line_to_macro(line, &current_macro);
                current_line = current_macro->first_line;
            }
            else {
                add_line(line, &current_line);
            }
        }
    }
    printf("hi");
}
