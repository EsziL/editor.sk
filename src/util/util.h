#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <gtk/gtk.h>

std::vector<std::string> split(const std::string& str, char delimiter);
GtkWidget* get_nth_child(GtkWidget *box, int n);
void save_text_to_file(GtkTextBuffer* buffer, const std::string& path);
std::string read_file_contents(const std::string& file_path);
std::string camelToTitle(std::string camelCase);

#endif // UTIL_H