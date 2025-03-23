#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "macro.h"
#include "marco_linked_list.h"
#include "macro_expander.h"

int main(int argc, char** argv) {

    FILE* fp = fopen("/Users/carmellwasserman/Desktop/example1.as", "r");
    FILE* fp2 = fopen("/Users/carmellwasserman/Desktop/example2.as", "w");
    struct macro *first_macro = NULL;

    separate_macros_from_file(fp, fp2, &first_macro);
}
