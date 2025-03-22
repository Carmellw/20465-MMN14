#include <stdio.h>
#include <string.h>

#include "consts.h"

int main(int argc, char** argv) {

    FILE* fp = fopen("/Users/carmellwasserman/Desktop/example1.as", "r");
    char line[MAX_LINE_LEN];
    int is_in_mcro = FALSE;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        if (FALSE == is_in_mcro && strncmp(line, "mcro", 4) == 0) {
            is_in_mcro = TRUE;

        }
        else if (TRUE == is_in_mcro && strncmp(line, "endmcro", 7) == 0) {
            is_in_mcro = FALSE;
        }
    }
    int i = 0;
    for (; i < argc; i++) {

    }
}
