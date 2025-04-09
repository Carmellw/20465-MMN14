#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "label.h"
#include "status_codes.h"

enum status_code first_pass_file(const char *file_path, struct label **labels, int *ic, int *dc);

#endif
