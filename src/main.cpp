#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <tuple>

static void aRedo(GApplication* app, gpointer data) {
    std::cout << "Undo" << std::endl;
}
static void aUndo(GApplication* app, gpointer data) {
    std::cout << "Redo" << std::endl;
}
static void aCut(GApplication* app, gpointer data) {
    std::cout << "Cut" << std::endl;
}

static void onActivate(GtkApplication* app, gpointer data) {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    GtkWidget *window;


    // Window init
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "editor.sk");
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    // Menu init

    // create menu bar

    // define actions

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

    // menubar finish

    gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menuBar));
    g_object_unref(menuBar);

    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

    // test label

    GtkWidget *label;

    label = gtk_label_new("Hello, World!");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), label);


    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.GtkApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(onActivate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
