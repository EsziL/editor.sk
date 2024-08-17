#ifndef FILEBAR_H
#define FILEBAR_H

#include <gtk/gtk.h>
#include <string>

void fileBarInit();
void fileBarShow();
void fileBarClose();
void fileBarOpenFile(std::string path);
void fileBarCloseFile_byButton(GtkButton *close, gpointer user_data);
void fileBarCloseFile(std::string path);
extern GtkWidget* gFileBar;

#endif // FILEBAR_H