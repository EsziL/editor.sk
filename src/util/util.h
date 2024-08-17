#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <sstream>
#include <gtk/gtk.h>

std::vector<std::string> split(const std::string& str, char delimiter);
GtkWidget* get_nth_child(GtkWidget *box, int n);

#endif // UTIL_H