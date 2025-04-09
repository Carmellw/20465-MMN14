#ifndef PATH_UTILS_H
#define PATH_UTILS_H

/**
 * Get a new file path based on a file path
 * @param path - the path to base on
 * @param add_to_name - anything to add to the name of the file (can be null)
 * @param new_extension - the extension to change the file to
 * @return
 */
char *get_new_path(const char *path, const char *add_to_name, const char *new_extension);

#endif
