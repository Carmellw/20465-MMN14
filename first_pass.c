#include <stdio.h>

#include "consts.h"
#include "first_pass.h"

#include <ctype.h>
#include <string.h>

void first_pass_file(const char* file_path) {
    FILE *fp = fopen(file_path, "r");
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example4.txt", "w");
    char line[MAX_LINE_LEN];
    int ic = 100;
    int dc = 100;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        handle_line(line, fp2);
    }

    fclose(fp);
    fclose(fp2);
}

void handle_line(const char* line, FILE* file_to_write) {
    const char label[MAX_LABEL_LEN];

    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    if (get_label_if_exist(line, label)) {

    }


}

int get_label_if_exist(const char* line, char* label) {
    char temp_line[MAX_LINE_LEN];
    char *temp_label;
    int i = 0;

    if (strchr(line, ':') == NULL) {
        return FALSE;
    }

    strcpy(temp_line, line);
    temp_label = strtok(temp_line, ":");

    while (strlen(temp_label) > 0) {
        if (!isspace(temp_label[i])) {
            break;
        }
        temp_label++;
    }

    while (strlen(temp_label) > i) {
        if (!isalnum(temp_label[i])) {
            return FALSE; // should be error
        }
        i++;
    }

    strcpy(label, temp_label);
    return TRUE;
}
