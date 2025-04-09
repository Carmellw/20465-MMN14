#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "label.h"

/**
 * Creates the ob, ent, and ext files out of am file, ic, dc, and a list of labels
 * @param file_path - the am file
 * @param labels - the list of labels
 * @param ic - the number of code lines
 * @param dc - the number of data lines
 * @return status code that indicate if the pass was successful or not
 */
enum status_code second_pass_file(const char *file_path, struct label *labels, int ic, int dc);

#endif
