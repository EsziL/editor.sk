#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <gtk/gtk.h>

GtkWidget* createTextEditor(GtkWidget *window);

extern GtkTextBuffer *gBuffer;
extern GtkWidget *gHighlight;
extern GtkWidget *gOverlay;
extern GtkWidget *gWindow;


#endif // TEXTEDITOR_H