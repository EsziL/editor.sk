#include <gtk/gtk.h>
#include <iostream>

// 1.4 -> the ratio between height of text view and font size
// multiple 1.4 by any number to get the height of the highlight box proportionally to the text view

struct EditorData {
    GtkTextBuffer *buffer;
    GtkWidget *highlight;
    GtkWidget *overlay;
    GtkWidget *window;
};


static int textViewLines(GtkTextBuffer *buffer) {
    GtkTextIter iter;
    int line_count = 0;
    gtk_text_buffer_get_start_iter(buffer, &iter);
    if (gtk_text_iter_is_end(&iter)) {
        return 0;
    }
    do {
        line_count++;
    } while (gtk_text_iter_forward_line(&iter));
    return line_count;
}

static int getCursorLine(GtkTextBuffer *buffer) {
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));
    return gtk_text_iter_get_line(&iter) + 1;
}

static void onEditorPositionChange(GtkTextBuffer *buffer, const GtkTextIter *location, GtkTextMark *mark, gpointer userData) {
    static int lastLine = -1;
    EditorData *data = static_cast<EditorData*>(userData);
    int currentLine = getCursorLine(buffer);
    if (currentLine != lastLine) {
        lastLine = currentLine;
        gtk_widget_set_margin_top(data->highlight, 28 * (currentLine - 1));

        int lines = textViewLines(data->buffer);

        gtk_widget_set_size_request(data->overlay, -1, (gtk_widget_get_height(data->window)-62+(28*lines)));
    }
}

GtkWidget* createTextEditor(GtkWidget *window) {
    GtkWidget *bgr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(bgr, "bgr");
    gtk_widget_set_hexpand(bgr, TRUE);
    gtk_widget_set_vexpand(bgr, TRUE);

    GtkWidget *overlay = gtk_overlay_new();
    gtk_widget_set_hexpand(overlay, TRUE);
    gtk_widget_set_vexpand(overlay, TRUE);

    GtkWidget *textView = gtk_text_view_new();
    gtk_widget_add_css_class(textView, "textview");
    gtk_widget_set_hexpand(textView, TRUE);
    gtk_widget_set_vexpand(textView, TRUE);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    GtkWidget *highlight = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(highlight, -1, 28);
    gtk_widget_add_css_class(highlight, "highlight");
    gtk_widget_set_halign(highlight, GTK_ALIGN_FILL);
    gtk_widget_set_valign(highlight, GTK_ALIGN_START);

    gtk_overlay_set_child(GTK_OVERLAY(overlay), bgr);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), highlight);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), textView);

    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_hexpand(scrolledWindow, TRUE);
    gtk_widget_set_vexpand(scrolledWindow, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), overlay);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


    EditorData *data = new EditorData();
    data->buffer = buffer;
    data->highlight = highlight;
    data->overlay = overlay;
    data->window = window;

    g_signal_connect(buffer, "mark-set", G_CALLBACK(onEditorPositionChange), data);

    return scrolledWindow;
}