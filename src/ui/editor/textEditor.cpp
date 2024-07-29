#include "textEditor.h"
#include <iostream>

// 1.4 -> the ratio between height of text view and font size
// multiple 1.4 by any number to get the height of the highlight box porportionally to the text view

struct EditorData {
    GtkTextBuffer *buffer;
    GtkWidget *highlight;
};

static int getCursorLine(GtkTextBuffer *buffer) {
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));
    return gtk_text_iter_get_line(&iter)+1;
}

static void onEditorPositionChange(GtkTextBuffer *buffer, const GtkTextIter *location, GtkTextMark *mark, gpointer userData) {
    static int lastLine = -1;
    EditorData *data = static_cast<EditorData*>(userData);
    int currentLine = getCursorLine(buffer);
    if (currentLine != lastLine) {
        lastLine = currentLine;
        gtk_widget_set_margin_top(data->highlight, 28*(currentLine - 1));
    }
}

GtkWidget* createTextEditor() {

    // Create the background box
    GtkWidget *bgr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(bgr, "bgr");
    gtk_widget_set_hexpand(bgr, TRUE);
    gtk_widget_set_vexpand(bgr, TRUE);

    // Create the overlay
    GtkWidget *overlay = gtk_overlay_new();
    gtk_widget_set_hexpand(overlay, TRUE);
    gtk_widget_set_vexpand(overlay, TRUE);

    // Create the text view
    GtkWidget *textView = gtk_text_view_new();
    gtk_widget_add_css_class(textView, "textview");
    gtk_widget_set_hexpand(textView, TRUE);
    gtk_widget_set_vexpand(textView, TRUE);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    // Create the highlight box
    GtkWidget *highlight = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(highlight, -1, 28);
    gtk_widget_add_css_class(highlight, "highlight");
    gtk_widget_set_halign(highlight, GTK_ALIGN_FILL);  // Align highlight to fill horizontally
    gtk_widget_set_valign(highlight, GTK_ALIGN_START); // Align highlight to the start vertically

    // Add the text view and highlight box to the overlay
    gtk_overlay_set_child(GTK_OVERLAY(overlay), highlight); 
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), textView);

    // Add the overlay to the background box
    gtk_box_append(GTK_BOX(bgr), overlay);

    // Create and initialize the EditorData structure
    EditorData *data = new EditorData();
    data->buffer = buffer;
    data->highlight = highlight;

    // Connect the 'mark-set' signal to the signal handler
    g_signal_connect(buffer, "mark-set", G_CALLBACK(onEditorPositionChange), data);

    return bgr;
}