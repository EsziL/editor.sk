#include "menuActionsList.h"
#include "menuBarActions.h"
#include <vector>
#include <tuple>
#include <iostream>

std::vector<std::tuple<GSimpleAction **, const gchar *, GCallback>> getActions() {
    static GSimpleAction *undoAction;
    static GSimpleAction *redoAction;
    static GSimpleAction *cutAction;
    static GSimpleAction *openFileAction;

    return {
        {&undoAction, "undo", G_CALLBACK(aRedo)},
        {&redoAction, "redo", G_CALLBACK(aUndo)},
        {&cutAction, "cut", G_CALLBACK(aCut)},
        {&openFileAction, "openFile", G_CALLBACK(aOpenFile)},
    };
}