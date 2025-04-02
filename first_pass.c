#include <stdio.h>

#include "consts.h"
#include "first_pass.h"

#include <ctype.h>
#include <string.h>

void first_pass_file(char* file_path) {
    FILE *fp = fopen(file_path, "r");
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example4.txt", "w");
    char line[MAX_LINE_LEN];

    while (fgets(line, MAX_LINE_LEN, fp)) {
        handle_line(line, fp2);
    }

    fclose(fp);
    fclose(fp2);
}

void handle_line(char* line, FILE* file_to_write) {
    const char *label = NULL;
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    label = get_label_if_exist(line);
    if (label != NULL) {

    }


}

char *get_label_if_exist(char* line) {
    char *label = strtok(line, ":");
    int i = 0;

    while (strlen(label) > 0) {
        if (!isspace(label[i])) {
            break;
        }
        label++;
    }

    while (strlen(label) > i) {
        if (!isalnum(label[i])) {
            return NULL;
        }
        i++;
    }

    return label;
}
