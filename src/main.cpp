#include "ui/menu/menuBar.h"
#include "ui/editor/textEditor.h"
#include "ui/css/cssLoader.h"
#include "ui/etc/error.h"
#include "ui/etc/fileBar.h"
#include "util/util.h"
#include "main.h"
#include <curl/curl.h>
#include <iostream>
#include <fstream>

GtkWidget *mainWindow = NULL;
std::string version = "alpha-1.0.1";

static gboolean on_key_pressed(GtkEventController* controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data) {
    if ((state & GDK_CONTROL_MASK) && keyval == GDK_KEY_s && fileCount > 0) {
        GtkWidget *close = get_nth_child(std::next(fileBarMap.begin(), 0)->second, 1);

        gtk_button_set_label(GTK_BUTTON(close), "×");

        std::string contents;
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(gBuffer, &start, &end);
        contents = gtk_text_buffer_get_text(gBuffer, &start, &end, false);

        std::string filename = currentPath;
        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file << contents;
            file.close();
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return FALSE;
}


static void onActivate(GtkApplication* app, gpointer data) {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Window init

    mainWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "editor.sk");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), WIDTH, HEIGHT);

    GtkWidget *textEditor = createTextEditor(mainWindow);
    errorBoxInit();
    fileBarInit();
    initCSS();
    // Menu init

    GtkWidget *winBox = gtk_overlay_new();
    gtk_widget_set_hexpand(winBox, TRUE);
    gtk_widget_set_vexpand(winBox, TRUE);

    GMenu *menuBar = createMenuBar(app);
    gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menuBar));
    g_object_unref(menuBar);
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(mainWindow), TRUE);


    gtk_overlay_set_child(GTK_OVERLAY(winBox), textEditor);
    gtk_overlay_add_overlay(GTK_OVERLAY(winBox), gFileBar);
    gtk_overlay_add_overlay(GTK_OVERLAY(winBox), gErrorBox);

    GtkEventController *controller = gtk_event_controller_key_new();

    g_signal_connect(controller, "key-pressed", G_CALLBACK(on_key_pressed), NULL);
    gtk_widget_add_controller(mainWindow, controller);

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