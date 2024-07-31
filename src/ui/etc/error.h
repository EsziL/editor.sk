#ifndef HIGHLIGHTS_H
#define HIGHLIGHTS_H

#include <gtk/gtk.h>
#include <string>

void showError(const std::string& message);
void errorBoxInit();

extern GtkWidget* gErrorBox;

#endif // HIGHLIGHTS_H
