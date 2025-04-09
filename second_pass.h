#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "label.h"

enum status_code second_pass_file(const char *file_path, struct label *labels, int ic, int dc);

#endif
