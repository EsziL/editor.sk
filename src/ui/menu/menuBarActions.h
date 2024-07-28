#ifndef MENUBARACTIONS_H
#define MENUBARACTIONS_H

#include <gtk/gtk.h>
#include <iostream>

void aRedo(GApplication* app, gpointer data);
void aUndo(GApplication* app, gpointer data);
void aCut(GApplication* app, gpointer data);
void aOpenFile(GApplication* app, gpointer data);

#endif // MENUBARACTIONS_H