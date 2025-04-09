#include <string.h>

#include "path_utils.h"

#include <stdlib.h>

char *get_new_path(const char *path, const char *add_to_name, const char *new_extension) {
    int path_length;
    char *new_path;
    char *dot;

    path_length = strlen(path) + strlen(new_extension) + 1;
    if(add_to_name != NULL) {
        path_length += strlen(add_to_name);
    }

    new_path = malloc(path_length);

    strcpy(new_path, path);
    dot = strrchr(new_path, '.');

    if (dot != NULL) {
        *dot = '\0';
    }

    if (add_to_name != NULL) {
        strcat(new_path, add_to_name);
    }

    strcat(new_path, ".");
    strcat(new_path, new_extension);

    return new_path;
}
