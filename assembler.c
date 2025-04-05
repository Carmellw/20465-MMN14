#include <stdio.h>
#include <stdlib.h>

#include "first_pass.h"
#include "macro.h"
#include "marco_linked_list.h"
#include "macro_expander.h"

int main(int argc, char** argv) {
    char *result;
    expand_macros("/Users/carmellwasserman/Desktop/test4.as", &result);
    printf("%s\n", result);

    first_pass_file(result);
}
