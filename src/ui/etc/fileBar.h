#ifndef FILEBAR_H
#define FILEBAR_H

#include <gtk/gtk.h>
#include <string>
#include <map>

void fileBarInit();
void fileBarShow();
void fileBarClose();
void fileBarOpenFile(std::string path);
void fileBarCloseFile_byButton(GtkButton *close, gpointer user_data);
void fileBarCloseFile(std::string path);
void fileBarSwitchFile_byButton(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data);
void fileBarSwitchFile(std::string path);
extern GtkWidget* gFileBar;
extern int fileCount;
extern std::map<std::string, GtkWidget*> fileBarMap;
extern std::string currentPath;

#endif // FILEBAR_H