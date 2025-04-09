#ifndef LINE_UTILS_H
#define LINE_UTILS_H

#include "label.h"
#include "status_codes.h"

/**
 * Gets the label name out from a line of code if there is any
 * @param line - the line to search in
 * @param type - the type if line
 * @param label_name - the returned label name
 * @return if a label was found in the line
 */
int get_label_name_if_exist(const char* line, const enum line_type type, char label_name[]);

/**
 *Get the type of a line
 * @param line - the line
 * @param type - the returned type
 * @return status code that indicate if we got line type successfully
 */
enum status_code get_line_type(const char *line, enum line_type *type);

/**
 * Check if a word is an instruction
 * @param word - the word
 * @return if a word is an instruction
 */
int is_instruction(const char *word);

/**
 * Checks if a word is a data instruction
 * @param word - the word
 * @return if a word is a data instruction
 */
int is_data_instruction(const char *word);

/**
 * Get the data type from a data instruction
 * @param word - the data instruction
 * @param type - the returned type
 * @return status code that indicate if we got data type successfully
 */
enum status_code get_data_type(const char *word, enum data_type *type);

/**
 * Trim white spaces from the start of the line
 * @param line - the line
 */
void trim_whitespaces_from_start(const char *line);

/**
 * Checks if a string is a register
 * @param str  - the string to check
 * @return if the string is a register
 */
int is_register(const char *str);

/**
 * Checks if a string is a number
 * @param str - the string to check
 * @return if the string is a number
 */
int is_number(const char *str);

/**
 * Checks if label name is a legal label name
 * @param label - the label name to check
 * @return if the label name is a legal label name
 */
int is_legal_label(const char *label);

#endif
