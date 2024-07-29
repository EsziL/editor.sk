#include "ui/menu/menuBar.h"
#include "ui/editor/textEditor.h"
#include "ui/css/cssLoader.h"
#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <tuple>



static void onActivate(GtkApplication* app, gpointer data) {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    GtkWidget *window;

    initCSS();

    // Window init

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "editor.sk");
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    // Menu init

    GMenu *menuBar = createMenuBar(app);
    gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menuBar));
    g_object_unref(menuBar);
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

    // Text Editor init

    GtkWidget *textEditor = createTextEditor();
    gtk_window_set_child(GTK_WINDOW(window), textEditor);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.eszil.editorsk", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(onActivate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    std::cout << "Exited with status " << status << std::endl;
    return status;
}
