#include "error.h"
#include <iostream>



GtkWidget* gErrorBox = NULL;
GtkWidget* errorLabel = NULL;

void errorBoxInit() {
    gErrorBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_visible(gErrorBox, FALSE);
    gtk_widget_set_size_request(gErrorBox, 150, 50);
    gtk_widget_set_halign(gErrorBox, GTK_ALIGN_END);
    gtk_widget_set_valign(gErrorBox, GTK_ALIGN_END);
}

gboolean hideError(gpointer widget) {
    if (errorLabel != NULL) {
        gtk_widget_set_visible(gErrorBox, FALSE);
        gtk_widget_remove_css_class(gErrorBox, "errorBox");
    }
    return G_SOURCE_REMOVE;
}

void showError(const std::string& message) {
    if (errorLabel != NULL) {
        gtk_box_remove(GTK_BOX(gErrorBox), errorLabel);
    }
    gtk_widget_set_visible(gErrorBox, TRUE);
    errorLabel = gtk_label_new(message.c_str());
    gtk_box_append(GTK_BOX(gErrorBox), errorLabel);
    gtk_widget_set_halign(errorLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(errorLabel, GTK_ALIGN_CENTER);
    gtk_widget_add_css_class(gErrorBox, "errorBox");

    g_timeout_add(4000, hideError, NULL);
}
