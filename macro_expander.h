#ifndef MACRO_EXPANDER_H
#define MACRO_EXPANDER_H

#include "macro_expander.h"
#include "status_codes.h"

/**
 * Takes a file and returns a new one with all its macros expanded
 * @param file_path - the file the read
 * @param result_file_path - the returned file path of the new file
* @return status_code that indicate if the macro expansion was successful or not
 */
enum status_code expand_macros(const char *file_path, char **result_file_path);

#endif
