#ifndef LABEL_LINKED_LIST_H
#define LABEL_LINKED_LIST_H

#include "label.h"

void add_label(const char *name, const enum line_type type, const int address, struct label **last_label);

void free_labels(struct label *first_line);

#endif
