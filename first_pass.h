#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "label.h"
#include "status_codes.h"

/**
 * Does the first pass on the file where we get the ic, dc and the list of labels
 * @param file_path - the file to do the first pass on
 * @param labels - the labels list to fill up
 * @param ic - the code lines counter
 * @param dc - the data lines counter
 * @return status code that indicate if the pass was successful or not
 */
enum status_code first_pass_file(const char *file_path, struct label **labels, int *ic, int *dc);

#endif
