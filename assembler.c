#include <stdio.h>
#include <stdlib.h>

#include "first_pass.h"
#include "status_codes.h"
#include "macro_expander.h"
#include "second_pass.h"
#include "label_linked_list.h"

int main(const int argc, char **argv) {
    char *result = NULL;
    struct label *labels = NULL;
    int ic = 100;
    int dc = 0;
    enum status_code status_code;
    int i;

    for (i = 1; i < argc; i++) {
        printf("processing file \"%s\"\n", argv[i]);
        status_code = expand_macros(argv[i], &result);
        if (status_code != SUCCESS) {
            fprintf(stderr, "Error expanding macros for file %s, moving to next file...\n", argv[i]);
            if (result != NULL) {
                free(result);
            }
            continue;
        }
        status_code = first_pass_file(result, &labels, &ic, &dc);
        if (status_code != SUCCESS) {
            fprintf(stderr, "Error at first pass for file %s, moving to next file...\n", argv[i]);
            if (result != NULL) {
                free(result);
            }
            if (labels != NULL) {
                free_labels(labels);
            }
            continue;
        }
        status_code = second_pass_file(result, labels, ic, dc);
        if (status_code != SUCCESS) {
            fprintf(stderr, "Error at second pass for file %s\n", argv[i]);
        }

        if (result != NULL) {
            free(result);
        }
        if (labels != NULL) {
            free_labels(labels);
        }

        ic = 100;
        dc = 0;
    }

    return SUCCESS;
}
