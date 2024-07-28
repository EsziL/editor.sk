#include <gtk/gtk.h>
#include <iostream>

static void on_activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *label;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "editor.sk");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

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
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
