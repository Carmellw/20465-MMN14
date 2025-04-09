#ifndef LABEL_LINKED_LIST_H
#define LABEL_LINKED_LIST_H

#include "label.h"
#include "status_codes.h"

/**
 * Add a new label new a list of labels
 * @param name - the name of the label
 * @param type - the type of the label
 * @param address - the address of the label
 * @param last_label - the current last label
 */
void add_label(const char *name, const enum line_type type, const int address, struct label **last_label);

/**
 * Free the storage of a label list
 * @param first_label - the first label of the list of labels
 */
void free_labels(struct label *first_label);

/**
 * Get a label struct by the name of the label
 * @param name - the name of the label
 * @param labels - the list of labels
 * @param label - the returned label
 * @return status_code that indicate if we found the label
 */
enum status_code get_label(const char *name, const struct label *labels, struct label *label);

/**
 * Returns if a label exists in a list of labels
 * @param name - the name of the label to check
 * @param labels - the list of labels
 * @return - TRUE (1) if the label exist FALSE (0) if not
 */
int is_label_exists(const char *name, const struct label *labels);

#endif
