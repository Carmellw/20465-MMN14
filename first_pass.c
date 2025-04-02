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
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    if (contain_label(line)) {
    }

}

int contain_label(char* line) {
    const char *label = strtok(line, ":");
    int i = 0;

    while (strlen(label) > i) {
        if (!isspace(label[i])) {
            break;
        }
    }

    while (strlen(label) > i) {
        if (!isalnum(label[i])) {
            return FALSE;
        }
    }

    return TRUE;
}

char *get_label(char* line) {

}
