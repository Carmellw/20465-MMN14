#include <stdio.h>
#include <stdlib.h>

#include "first_pass.h"
#include "macro.h"
#include "marco_linked_list.h"
#include "macro_expander.h"
#include "second_pass.h"

int main(int argc, char** argv) {
    char *result;
    struct label *labels = NULL;
    struct entry *entries = NULL;
    int ic = 100;
    int dc = 0;

    expand_macros("/Users/carmellwasserman/Desktop/ps.as", &result);
    printf("%s\n", result);

    first_pass_file(result, &labels, &entries, &ic, &dc);
    second_pass_file(result, labels, entries, ic, dc);
}
