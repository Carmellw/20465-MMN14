#ifndef MACRO_EXPANDER_H
#define MACRO_EXPANDER_H

#include "macro_expander.h"
#include "status_codes.h"

enum status_code expand_macros(const char *file_path, const char **result_file_path);

#endif //MACRO_EXPANDER_H
