#include "menuBar.h"
#include "menuBarActions.h"
#include <vector>
#include <tuple>

GMenu* createMenuBar(_GtkApplication* app) {
    GSimpleAction *undoAction;
    GSimpleAction *redoAction;
    GSimpleAction *cutAction;

    std::vector<std::tuple<GSimpleAction **, const gchar *, GCallback>> actions = {
        {&undoAction, "undo", G_CALLBACK(aRedo)},
        {&redoAction, "redo", G_CALLBACK(aUndo)},
        {&cutAction, "cut", G_CALLBACK(aCut)}
    };

    for (auto &action : actions) {
        GSimpleAction **actionPtr = std::get<0>(action);
        const gchar *actionName = std::get<1>(action);
        GCallback actionCallback = std::get<2>(action);

        *actionPtr = g_simple_action_new(actionName, NULL);
        g_signal_connect(*actionPtr, "activate", actionCallback, NULL);
        g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(*actionPtr));
    }

    GMenu *menuBar = g_menu_new();
    GMenu *menu;
    GMenuItem *menuItem;

    // file menu

    menu = g_menu_new();
    menuItem = g_menu_item_new("File", NULL);
    g_menu_append_item(menu, menuItem);
    g_object_unref(menuItem);

    // edit menu

    menu = g_menu_new();
    menuItem = g_menu_item_new("Edit", NULL);
    
    GMenu *editMenu = g_menu_new();
    GMenuItem *editUndoItem = g_menu_item_new("Undo", "app.undo");
    GMenuItem *editRedoItem = g_menu_item_new("Redo", "app.redo");
    GMenuItem *editCutItem = g_menu_item_new("Cut", "app.cut");

    for (GMenuItem *item : {editUndoItem, editRedoItem, editCutItem}) {
        g_menu_append_item(editMenu, item);
        g_object_unref(item);
    }

    g_menu_item_set_submenu(menuItem, G_MENU_MODEL(editMenu));
    g_menu_append_item(menuBar, menuItem);
    g_object_unref(editMenu);
    g_object_unref(menuItem);

    return menuBar;
}