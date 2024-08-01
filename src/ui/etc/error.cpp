#include "error.h"
#include <iostream>
#include <queue>
#include <string>

GtkWidget* gErrorBox = NULL;
GtkWidget* errorLabel = NULL;
guint hideErrorTimeoutId = 0;
std::queue<std::string> errorQueue;

gboolean showNextError(gpointer data);

void errorBoxInit() {
    gErrorBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_visible(gErrorBox, FALSE);
    gtk_widget_set_size_request(gErrorBox, 150, 50);
    gtk_widget_set_halign(gErrorBox, GTK_ALIGN_END);
    gtk_widget_set_valign(gErrorBox, GTK_ALIGN_END);
}

gboolean hideError(gpointer widget) {
    gtk_widget_set_visible(gErrorBox, FALSE);
    gtk_widget_remove_css_class(gErrorBox, "errorBox");
    hideErrorTimeoutId = 0;

    if (!errorQueue.empty()) g_timeout_add(50, showNextError, NULL);
    return G_SOURCE_REMOVE;
}

gboolean addCssClass(gpointer widget) {
    gtk_widget_add_css_class(GTK_WIDGET(widget), "errorBox");
    return G_SOURCE_REMOVE;
}

gboolean showNextError(gpointer data) {
    if (!errorQueue.empty()) {
        std::string nextError = errorQueue.front();
        errorQueue.pop();
        showError(nextError);
    }
    return G_SOURCE_REMOVE;
}

void showError(const std::string& message) {
    if (gtk_widget_is_visible(gErrorBox)) {
        errorQueue.push(message);
        return;
    }


    gtk_widget_set_visible(gErrorBox, TRUE);
    gtk_widget_remove_css_class(gErrorBox, "errorBox");

    if (errorLabel == NULL) {
        errorLabel = gtk_label_new(message.c_str());
        gtk_box_append(GTK_BOX(gErrorBox), errorLabel);
        gtk_widget_set_halign(errorLabel, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(errorLabel, GTK_ALIGN_CENTER);
        gtk_widget_set_hexpand(errorLabel, TRUE);
        gtk_widget_set_vexpand(errorLabel, TRUE);
    } else {
        gtk_label_set_text(GTK_LABEL(errorLabel), message.c_str());
    }

    g_timeout_add(50, addCssClass, gErrorBox);

    if (hideErrorTimeoutId != 0) g_source_remove(hideErrorTimeoutId);


    hideErrorTimeoutId = g_timeout_add(4000, hideError, NULL);
}