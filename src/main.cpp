#include "ui/menu/menuBar.h"
#include "ui/editor/textEditor.h"
#include "ui/css/cssLoader.h"
#include "ui/etc/error.h"
#include "main.h"
#include <iostream>
#include <vector>
#include <tuple>

GtkWidget *mainWindow = NULL;

static void onActivate(GtkApplication* app, gpointer data) {
    const int WIDTH = 800;
    const int HEIGHT = 600;



    // Window init

    mainWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "editor.sk");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), WIDTH, HEIGHT);

    initCSS();
    errorBoxInit();
    // Menu init

    GtkWidget *winBox = gtk_overlay_new();

    GMenu *menuBar = createMenuBar(app);
    gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menuBar));
    g_object_unref(menuBar);
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(mainWindow), TRUE);


    GtkWidget *textEditor = createTextEditor(mainWindow);

    gtk_overlay_set_child(GTK_OVERLAY(winBox), textEditor);
    gtk_overlay_add_overlay(GTK_OVERLAY(winBox), gErrorBox);
    
    gtk_window_set_child(GTK_WINDOW(mainWindow), winBox);
    
    gtk_window_present(GTK_WINDOW(mainWindow));
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