#ifndef MARCO_LINKED_LIST_H
#define MARCO_LINKED_LIST_H

/**
 * Add a new macro to a list of macros
 * @param name - the name of the macro
 * @param last_macro - the current last macro of the list of macros
 */
void add_macro(const char *name, struct macro **last_macro);

/**
 * Add a new line to a list of lines
 * @param line_content - the content of the line
 * @param last_line - the current last line of the list of lines
 */
void add_line(const char *line_content, struct line **last_line);

/**
 * Adds the first line for the list of line of a macro
 * @param line_content - the content of the line
 * @param macro - the macro to add the first line to
 */
void add_first_line_to_macro(const char *line_content, struct macro **macro);

/**
 * Free the list of macros
 * @param first_macro - the first macro of the list of macros
 */
void free_macros(struct macro *first_macro);

/**
 * Checks if a macro exists in a list of macros
 * @param name - the name if the macro to check
 * @param macros - the list macros
 * @return if the macro exists in the list of macros
 */
int is_macro_exists(const char *name, const struct macro *macros);

#endif
