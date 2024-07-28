#include "menuBarActions.h"
#include <iostream>

void aRedo(GApplication* app, gpointer data) {
    std::cout << "Undo" << std::endl;
}
void aUndo(GApplication* app, gpointer data) {
    std::cout << "Redo" << std::endl;
}
void aCut(GApplication* app, gpointer data) {
    std::cout << "Cut" << std::endl;
}