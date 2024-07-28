#include "textEditor.h"
#include <iostream>

GtkWidget* createTextEditor() {

    GtkWidget *textView = gtk_text_view_new();

    gtk_widget_set_hexpand(textView, TRUE);
    gtk_widget_set_vexpand(textView, TRUE);

    gtk_widget_add_css_class(textView, "textview");

    gtk_widget_set_size_request(textView, 800, 600);

    

    

    return textView;
}